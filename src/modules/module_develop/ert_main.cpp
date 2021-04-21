//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
//
// Code generated for Simulink model 'matlab_module'.
//
// Model version                  : 1.7
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Wed Apr 21 18:10:14 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
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
#include "matlab_module.h"
#define STEP_SIZE                      200000UL                  // Sample Time in microseconds 

static pthread_mutex_t matlab_module_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t matlab_module_condition = PTHREAD_COND_INITIALIZER;
int_T matlab_moduleModule::custom_command(int_T argc, char_T *argv[])
{
  return print_usage("unknown command\n");
}

int_T matlab_moduleModule::print_usage(const char_T *reason)
{
  return 0;
}

int_T matlab_moduleModule::task_spawn(int_T argc, char_T *argv[])
{
  _task_id = os_task_spawn_cmd("matlab_module",
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

matlab_moduleModule *matlab_moduleModule::instantiate(int_T argc, char_T *argv[])
{
  matlab_moduleModule *instance = new matlab_moduleModule();
  if (instance == nullptr) {
    printf("alloc failed\n");
  }

  return instance;
}

static void matlab_module_timer_handler(int signo)
{
  int status;

  // Check signo
  if (signo == SIGALRM) {
    pthread_mutex_lock(&matlab_module_mutex);
    if (pthread_cond_broadcast(&matlab_module_condition) != OK) {
      printf("ERROR\n");
    }

    pthread_mutex_unlock(&matlab_module_mutex);
  } else {
    status = 0;

    // Wake sleeping consumer
    //if (status != OK)
    //ERR("pthread_cond_signal error.");
  }
}

static void *matlab_module_main_timer_thread(FAR void *para)
{
  int status;
  matlab_module_initialize();
  while (1) {
    status = pthread_mutex_lock(&matlab_module_mutex);
    status = pthread_cond_wait(&matlab_module_condition, &matlab_module_mutex);
    status = pthread_mutex_unlock(&matlab_module_mutex);
    DEBUG("matlab_module step\n");
    matlab_module_step();

    // Get model outputs here
  }

  matlab_module_terminate();
  pthread_exit(NULL);
  return NULL;                    // Non-reachable -- needed for some compilers
}

void matlab_moduleModule::run()
{
  printf("matlab_module started.\n");

  // Set timer timeout action
  act.sa_handler = &matlab_module_timer_handler;
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
  timer.it_value.tv_sec = 10;
  timer.it_value.tv_nsec = 0;
  timer.it_interval.tv_sec = 10;       //(STEP_SIZE/USEC_PER_SEC);
  timer.it_interval.tv_nsec = 0;       //(STEP_SIZE*NSEC_PER_USEC);
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
    matlab_module_main_timer_thread, NULL);
  if (status != OK) {
    printf("ERROR: thread creation failed\n");
    goto errorout;
  }

  for (;;) {
    sched_yield();
  }

 errorout:
  pthread_mutex_destroy(&matlab_module_mutex);
  pthread_cond_destroy(&matlab_module_condition);
}

int_T matlab_module_main(int_T argc, char_T *argv[])
{
  return matlab_moduleModule::main(argc, argv);
}

//
// File trailer for generated code.
//
// [EOF]
//
