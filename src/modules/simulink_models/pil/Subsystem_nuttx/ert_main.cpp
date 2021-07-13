//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
//
// Code generated for Simulink model 'Subsystem'.
//
// Model version                  : 1.8
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Jun  2 13:31:59 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Custom Processor->Custom
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
#include "Subsystem.h"
#define STEP_SIZE                      10000UL                   // Sample Time in microseconds 

static pthread_mutex_t Subsystem_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t Subsystem_condition = PTHREAD_COND_INITIALIZER;
int_T SubsystemModule::custom_command(int_T argc, char_T *argv[])
{
  return print_usage("unknown command\n");
}

int_T SubsystemModule::print_usage(const char_T *reason)
{
  return 0;
}

int_T SubsystemModule::task_spawn(int_T argc, char_T *argv[])
{
  _task_id = os_task_spawn_cmd("Subsystem",
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

SubsystemModule *SubsystemModule::instantiate(int_T argc, char_T *argv[])
{
  SubsystemModule *instance = new SubsystemModule();
  if (instance == nullptr) {
    printf("alloc failed\n");
  }

  return instance;
}

static void Subsystem_timer_handler(int signo)
{
  int status;

  // Check signo
  if (signo == SIGALRM) {
    pthread_mutex_lock(&Subsystem_mutex);
    if (pthread_cond_broadcast(&Subsystem_condition) != OK) {
      printf("ERROR\n");
    }

    pthread_mutex_unlock(&Subsystem_mutex);
  } else {
    status = 0;

    // Wake sleeping consumer
    //if (status != OK)
    //ERR("pthread_cond_signal error.");
  }
}

static void *Subsystem_main_timer_thread(FAR void *para)
{
  int status;
  Subsystem_initialize();
  while (1) {
    status = pthread_mutex_lock(&Subsystem_mutex);
    status = pthread_cond_wait(&Subsystem_condition, &Subsystem_mutex);
    status = pthread_mutex_unlock(&Subsystem_mutex);
    DEBUG("Subsystem step\n");
    Subsystem_step();

    // Get model outputs here
  }

  Subsystem_terminate();
  pthread_exit(NULL);
  return NULL;                    // Non-reachable -- needed for some compilers
}

void SubsystemModule::run()
{
  printf("Subsystem started.\n");

  // Set timer timeout action
  act.sa_handler = &Subsystem_timer_handler;
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
    Subsystem_main_timer_thread, NULL);
  if (status != OK) {
    printf("ERROR: thread creation failed\n");
    goto errorout;
  }

  for (;;) {
    sched_yield();
  }

 errorout:
  pthread_mutex_destroy(&Subsystem_mutex);
  pthread_cond_destroy(&Subsystem_condition);
}

int_T Subsystem_main(int_T argc, char_T *argv[])
{
  return SubsystemModule::main(argc, argv);
}

//
// File trailer for generated code.
//
// [EOF]
//
