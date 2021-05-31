//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: rt_main.cpp
//
// Code generated for Simulink model 'pubsub_multitask'.
//
// Model version                  : 1.5
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun May 30 22:17:46 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include "rt_nonfinite.h"
#include "pubsub_multitask.h"
#include "rtwtypes.h"
#include "rt_main.h"
#define CHECK_STATUS(status, fcn)      if (status != 0) {fprintf(stderr, "Call to %s returned error status (%d).\n", fcn, status); perror(fcn); fflush(stderr); exit(EXIT_FAILURE);}

// Semaphores used for threads synchronization
sem_t quitSem[1];
sem_t periodicTaskStartSem[3];
sem_t periodicTaskStopSem[3];
sem_t periodicTriggerSem[1];
timer_t timers[1];
int threadID[3];
void MW_sem_wait(sem_t *sem)
{
  int status;
  while (((status = sem_wait(sem)) == -1) && (errno == EINTR)) {
    // Restart if interrupted by a signal
    continue;
  }

  CHECK_STATUS(status, "sem_wait");
}

void MW_blockSignal(int sigNo, sigset_t *sigMask)
{
  int ret;
  sigaddset(sigMask, sigNo);
  ret = pthread_sigmask(SIG_BLOCK, sigMask, (NULL));
  CHECK_STATUS(ret, "pthread_sigmask");
}

void MW_sigWait(sigset_t *sigMask)
{
  int ret;
  ret = sigwaitinfo(sigMask, (NULL));
  if (ret == -1) {
    fprintf(stderr, "Call to sigwait returned error.\n");
    perror("sigwait");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
}

void MW_setTaskPeriod(double periodInSeconds, int sigNo, int idx)
{
  struct sigevent sev;
  struct itimerspec its;
  int ret;

  // Create a timer
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = sigNo;
  sev.sigev_value.sival_int = idx;
  ret = timer_create(CLOCK_REALTIME, &sev, &timers[idx]);
  CHECK_STATUS(ret, "timer_create");

  // Real-time scheduling timer
  its.it_value.tv_sec = (time_t)periodInSeconds;
  its.it_value.tv_nsec = (periodInSeconds - (time_t)periodInSeconds) *
    1000000000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;
  ret = timer_settime(timers[idx], 0, &its, (NULL));
  CHECK_STATUS(ret, "timer_settime");
}

void MW_sem_waitTriggerWithOverrunDetection(sem_t *startSem, int triggerIdx)
{
  int ret;
  ret = sem_trywait(startSem);
  if (ret == -1) {
    if (errno == EAGAIN) {
      MW_sem_wait(startSem);
    } else {
      fprintf(stderr, "Call to sem_trywait returned error.\n");
      perror("sigtimedwait");
      fflush(stderr);
      exit(EXIT_FAILURE);
    }
  } else {
    printf("Overrun - periodic trigger %d base rate too fast.\n", triggerIdx);
    fflush(stdout);
  }
}

void MW_sem_waitTaskWithOverrunDetection(sem_t *stopSem, int taskIdx)
{
  int ret;
  ret = sem_trywait(stopSem);
  if (ret == -1) {
    if (errno == EAGAIN) {
      printf("Overrun - rate for periodic task %d too fast.\n", taskIdx);
      fflush(stdout);
      MW_sem_wait(stopSem);
    } else {
      fprintf(stderr, "Call to sem_trywait returned error.\n");
      perror(" sem_trywait");
      fflush(stderr);
      exit(EXIT_FAILURE);
    }
  }
}

void* periodicTask(void *arg)
{
  int ret;
  int taskId = *((int *) arg);
  int_T taskIdT = *((int_T *) arg);
  sigset_t ss;
  sigemptyset(&ss);
  MW_blockSignal(SIGALRM, &ss);
  while (1) {
    MW_sem_wait(&periodicTaskStartSem[taskId]);
    pubsub_multitask_step(taskIdT);

    // Get model outputs here
    ret = sem_post(&periodicTaskStopSem[taskId]);
    CHECK_STATUS(ret, "sem_post");
  }

  return (NULL);
}

void* baseRateTaskScheduler(void *arg)
{
  volatile boolean_T noErr;
  int ret;
  int_T i;
  int_T taskCounters[3] = { 0, 0, 0 };

  int_T taskTicks[3] = { 1, 10, 100 };

  int_T taskId[3] = { 0, 1, 2 };

  sigset_t ss;
  sigemptyset(&ss);
  MW_blockSignal(SIGALRM, &ss);

  // Unused arguments
  (void)(arg);
  noErr = (rtmGetErrorStatus(pubsub_multitask_M) == (NULL));
  while (noErr) {
    // Wait for the next timer interrupt
    MW_sem_waitTriggerWithOverrunDetection(&periodicTriggerSem[0], 0);
    for (i = 0; i < 3; i++) {
      if (taskCounters[i] == 0) {
        MW_sem_waitTaskWithOverrunDetection(&periodicTaskStopSem[taskId[i]], i);
      }
    }

    noErr = (rtmGetErrorStatus(pubsub_multitask_M) == (NULL));
    if (noErr) {
      for (i = 0; i <3; i++) {
        if (taskCounters[i] == 0) {
          ret = sem_post(&periodicTaskStartSem[taskId[i]]);
          CHECK_STATUS(ret, "sem_post");
        }
      }

      for (i = 0; i <3; i++) {
        taskCounters[i]++;
        if (taskCounters[i] > (taskTicks[i]-1)) {
          taskCounters[i] = 0;
        }
      }
    } else {
      for (i = 0; i < 3; i++) {
        if (taskCounters[i] != 0) {
          MW_sem_wait(&periodicTaskStopSem[taskId[i]]);
        }
      }
    }
  }                                    // while

  ret = sem_post(&quitSem[0]);
  CHECK_STATUS(ret, "sem_post");
  ret = timer_delete(timers[0]);
  CHECK_STATUS(ret, "timer_delete");
  return (NULL);
}

void sigHandler_TimerSignal(int signo, siginfo_t *sigInfo, void *ctx)
{
  int ret;

  // Unused arguments
  (void)(ctx);
  (void)(signo);
  switch ((*sigInfo).si_value.sival_int) {
   case 0:
    ret = sem_post(&periodicTriggerSem[0]);
    CHECK_STATUS(ret, "sem_post");
    break;
  }
}

int pubsub_multitask_entryPoint()
{
  int i;
  pthread_t periodicThread[3];
  pthread_t periodicTriggerThread[1];
  struct sched_param sp;
  int ret, policy;
  pthread_attr_t attr;
  double periodicTriggerRate[1];
  int priority[3];
  priority[0] = 39;
  priority[1] = 38;
  priority[2] = 37;
  periodicTriggerRate[0] = 0.001;
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(pubsub_multitask_M, 0);

  // Initialize semaphore used for thread synchronization
  for (i = 0; i < 1; i++) {
    ret = sem_init(&quitSem[i], 0, 0);
    CHECK_STATUS(ret, "sem_init:quitSem");
  }

  // Create threads executing the Simulink model
  pthread_attr_init(&attr);
  ret = pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
  CHECK_STATUS(ret, "pthread_attr_setinheritsched");
  ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  CHECK_STATUS(ret, "pthread_attr_setdetachstate");
  ret = pthread_attr_getschedpolicy(&attr, &policy);
  CHECK_STATUS(ret, "pthread_attr_getschedpolicy");

  // Initialize model
  pubsub_multitask_initialize();

  {
    // Connect and enable the signal handler for timers notification
    struct sigaction sa;
    sa.sa_sigaction = &sigHandler_TimerSignal;
    sigemptyset(&sa.sa_mask);

    //sa.sa_flags = SA_RESTART;  /* Restart functions if interrupted by handler
    sa.sa_flags |= SA_SIGINFO;     // Enable passing signal data to the handler
    if (sigaction(SIGALRM, &sa, (NULL)) == -1) {
      fprintf(stderr,
              "Failed to register signal handler for signal SIGALRM : %s\n",
              strerror(errno));
    }
  }

  // Create periodic threads
  for (i = 0; i < 3; i++) {
    ret = sem_init(&periodicTaskStartSem[i], 0, 0);
    CHECK_STATUS(ret, "sem_init");
    ret = sem_init(&periodicTaskStopSem[i], 0, 1);
    CHECK_STATUS(ret, "sem_init");
    threadID[i] = i;
    if (policy == SCHED_FIFO || policy == SCHED_RR) {
      sp.sched_priority = priority[i];
      ret = pthread_attr_setschedparam(&attr, &sp);
      CHECK_STATUS(ret, "pthread_attr_setschedparam");
    }

    ret = pthread_create(&periodicThread[i], &attr, periodicTask, (void *)
                         &threadID[i]);
    CHECK_STATUS(ret,"pthread_create");
  }

  // Initialize semaphores for periodic triggers
  for (i = 0; i < 1; i++) {
    ret = sem_init(&periodicTriggerSem[i], 0, 0);
    CHECK_STATUS(ret, "sem_init");
  }

  // Create periodic trigger threads
  if (policy == SCHED_FIFO || policy == SCHED_RR) {
    sp.sched_priority = 40;
    ret = pthread_attr_setschedparam(&attr, &sp);
    CHECK_STATUS(ret, "pthread_attr_setschedparam");
  }

  ret = pthread_create(&periodicTriggerThread[0], &attr, baseRateTaskScheduler,
                       (NULL));
  CHECK_STATUS(ret, "pthread_create");
  pthread_attr_destroy(&attr);

  // Create periodic timers
  for (i = 0; i < 1; i++) {
    MW_setTaskPeriod(periodicTriggerRate[i], SIGALRM, i);
  }

  // Wait for a stopping condition.
  for (i = 0; i < 1; i++) {
    MW_sem_wait(&quitSem[i]);
  }

  printf("**stopping the model**\n");
  fflush(stdout);
  if (rtmGetErrorStatus(pubsub_multitask_M) != (NULL)) {
    fprintf(stderr, "\n**%s**\n", rtmGetErrorStatus(pubsub_multitask_M));
  }

  // Disable rt_OneStep() here

  // Terminate model
  pubsub_multitask_terminate();

  {
    // Restore the signal handler for signal: SIGALRM
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);

    //sa.sa_flags = SA_RESTART;          /* Restart functions if interrupted by handler 
    if (sigaction(SIGALRM, &sa, (NULL)) == -1) {
      fprintf(stderr,
              "Failed to restore default signal handler for signal SIGALRM : %s\n",
              strerror(errno));
    }
  }

  for (i = 0; i < 3; i++) {
    ret = sem_destroy(&periodicTaskStartSem[i]);
    CHECK_STATUS(ret, "sem_destroy");
    ret = sem_destroy(&periodicTaskStopSem[i]);
    CHECK_STATUS(ret, "sem_destroy");
  }

  for (i = 0; i < 1; i++) {
    ret = sem_destroy(&periodicTriggerSem[i]);
    CHECK_STATUS(ret, "sem_destroy");
    ret = sem_destroy(&quitSem[i]);
    CHECK_STATUS(ret, "sem_destroy");
  }

  return 0;
}

int_T pubsub_multitask_module::custom_command(int_T argc, char_T *argv[])
{
  return print_usage("unknown command\n");
}

int_T pubsub_multitask_module::print_usage(const char_T *reason)
{
  return 0;
}

int_T pubsub_multitask_module::task_spawn(int_T argc, char_T *argv[])
{
  _task_id = os_task_spawn_cmd("pubsub_multitask",
    SCHED_DEFAULT,
    SCHED_PRIORITY_MAX,
    1024,
    (os_main_t)&run_trampoline,
    (char_T *const *)argv);
  if (_task_id < 0) {
    _task_id = -1;
    return -errno;
  }

  return 0;
}

pubsub_multitask_module *pubsub_multitask_module::instantiate(int_T argc, char_T
  *argv[])
{
  pubsub_multitask_module *instance = new pubsub_multitask_module();
  if (instance == nullptr) {
    printf("alloc failed\n");
  }

  return instance;
}

void pubsub_multitask_module::run()
{
  //Call module
  pubsub_multitask_entryPoint();
}

int_T pubsub_multitask_main(int_T argc, char_T *argv[])
{
  return pubsub_multitask_module::main(argc, argv);
}

//
// File trailer for generated code.
//
// [EOF]
//
