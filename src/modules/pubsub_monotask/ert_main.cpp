//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
//
// Code generated for Simulink model 'pubsub_monotask'.
//
// Model version                  : 1.3
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun May 30 21:24:27 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <signal.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <platform_common/log.h>
#include "ert_main.h"
#include "pubsub_monotask.h"
#define STEP_SIZE                      1000UL                    // Sample Time in microseconds 

static pthread_mutex_t pubsub_monotask_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t pubsub_monotask_condition = PTHREAD_COND_INITIALIZER;
int_T pubsub_monotaskModule::custom_command(int_T argc, char_T *argv[])
{
  return print_usage("unknown command\n");
}

int_T pubsub_monotaskModule::print_usage(const char_T *reason)
{
  return 0;
}

int_T pubsub_monotaskModule::task_spawn(int_T argc, char_T *argv[])
{
  _task_id = os_task_spawn_cmd("pubsub_monotask",
    SCHED_DEFAULT,
    SCHED_PRIORITY_DEFAULT,
    1024,
    (os_main_t)&run_trampoline,
    (char_T *const *)argv);
  if (_task_id < 0) {
    _task_id = -1;
    return -errno;
  }

  return 0;
}

pubsub_monotaskModule *pubsub_monotaskModule::instantiate(int_T argc, char_T
  *argv[])
{
  pubsub_monotaskModule *instance = new pubsub_monotaskModule();
  if (instance == nullptr) {
    printf("alloc failed\n");
  }

  return instance;
}

static void pubsub_monotask_timer_handler(int signo)
{
  int status;

  // Check signo
  if (signo == SIGALRM) {
    pthread_mutex_lock(&pubsub_monotask_mutex);
    if (pthread_cond_broadcast(&pubsub_monotask_condition) != OK) {
      printf("ERROR\n");
    }

    pthread_mutex_unlock(&pubsub_monotask_mutex);
  } else {
    status = 0;

    // Wake sleeping consumer
    //if (status != OK)
    //ERR("pthread_cond_signal error.");
  }
}

static void *pubsub_monotask_main_timer_thread(FAR void *para)
{
  int status;
  pubsub_monotask_initialize();
  while (1) {
    status = pthread_mutex_lock(&pubsub_monotask_mutex);
    status = pthread_cond_wait(&pubsub_monotask_condition,
      &pubsub_monotask_mutex);
    status = pthread_mutex_unlock(&pubsub_monotask_mutex);
    DEBUG("pubsub_monotask step\n");
    pubsub_monotask_step(0);

    // Get model outputs here
  }

  pubsub_monotask_terminate();
  pthread_exit(NULL);
  return NULL;                    // Non-reachable -- needed for some compilers
}

void pubsub_monotaskModule::run()
{
  printf("pubsub_monotask started.\n");

  // Set timer timeout action
  act.sa_handler = &pubsub_monotask_timer_handler;
  act.sa_flags = SA_SIGINFO;
  (void)sigfillset(&act.sa_mask);
  (void)sigdelset(&act.sa_mask, SIGALRM);
  status = sigaction(SIGALRM, &act, &oact);
  if (status != OK) {
    printf("%s: ERROR sigaction failed, status=%d\n" ,__FUNCTION__, status);
    goto errorout;
  }

  // Create the POSIX timer
  notify.sigev_notify = SIGEV_SIGNAL;
  notify.sigev_signo = SIGALRM;
  notify.sigev_value.sival_int = 0;

#ifdef CONFIG_SIG_EVTHREAD

  notify.sigev_notify_function = NULL;
  notify.sigev_notify_attributes = NULL;

#endif

  status = timer_create(CLOCK_MONOTONIC, &notify, &timerid);
  if (status != OK) {
    printf("%s: timer_create failed, errno=%d\n",__FUNCTION__, errno);
    goto errorout;
  }

  // Start the POSIX timer
  timer.it_value.tv_sec = (STEP_SIZE/USEC_PER_SEC);
  timer.it_value.tv_nsec = (STEP_SIZE%USEC_PER_SEC);
  timer.it_interval.tv_sec = (STEP_SIZE/USEC_PER_SEC);
  timer.it_interval.tv_nsec = (STEP_SIZE%USEC_PER_SEC);
  status = timer_settime(timerid, 0, &timer, NULL);
  if (status != OK) {
    printf("%s: timer_settime failed, errno=%d\n",__FUNCTION__, errno);
    goto errorout;
  }

  // Set main thread
  prio_min = sched_get_priority_min(SCHED_FIFO);
  prio_max = sched_get_priority_max(SCHED_FIFO);
  prio_mid = (prio_min + prio_max) / 2;
  sparam.sched_priority = (prio_mid + prio_max) / 2;
  status = pthread_attr_init(&attr);
  if (status != OK) {
    printf("ERROR: pthread_attr_init failed \n");
  }

  status = pthread_attr_setschedparam(&attr,&sparam);
  if (status != OK) {
    printf("ERROR: pthread_attr_setschedparam failed.\n");
    goto errorout;
  }

  pthread_t main_timer_threadid;
  status = pthread_create(&main_timer_threadid, &attr,
    pubsub_monotask_main_timer_thread, NULL);
  if (status != OK) {
    printf("ERROR: thread creation failed\n");
    goto errorout;
  }

  for (;;) {
    sched_yield();
  }

 errorout:
  pthread_mutex_destroy(&pubsub_monotask_mutex);
  pthread_cond_destroy(&pubsub_monotask_condition);
}

int_T pubsub_monotask_main(int_T argc, char_T *argv[])
{
  return pubsub_monotaskModule::main(argc, argv);
}

//
// File trailer for generated code.
//
// [EOF]
//
