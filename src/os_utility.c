#define _GNU_SOURCE
#include <sched.h>
#include <sys/time.h>
#include <pthread.h>
#include "os_define.h"
#include "os_log.h"

int64_t os_get_time()
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return (((int64_t) tp.tv_sec) * 1000000 + (int64_t) tp.tv_usec);
}

void os_bind_core(int64_t bind_core_id)
{
  if (-1 == bind_core_id) {
    // need not bind
  } else {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(bind_core_id, &cpuset);
    int tmp_ret = 0;
    if (0 != (tmp_ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset))) {
      OS_LOG(WARN, "bind_core fail, bind_core_id=%ld ret=%d", bind_core_id, tmp_ret);
    } else {
      OS_LOG(INFO, "bind_core succ, bind_core_id=%ld", bind_core_id);
    }
  }
}

