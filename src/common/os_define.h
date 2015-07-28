#ifndef OS_DEFINE_H_
#define OS_DEFINE_H_

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/syscall.h>

// some macro utilities
#ifdef __cplusplus
# define OS_CPP_START extern "C" {
# define OS_CPP_END }
#else
# define OS_CPP_START
# define OS_CPP_END
#endif

#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

// some macro functions
#define GETTID() syscall(__NR_gettid)
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
#define MIN(a,b) ((a) < (b)) ? (a) : (b)

// error numbers
#define OS_SUCCESS 0
#define OS_INVALID_PARAM -1

#define OS_TC_LOG_BUFFER_COUNT 16
#define OS_TC_LOG_BUFFER_SIZE 4096

#endif // OS_DEFINE_H_

