#ifndef OS_DEFINE_H_
#define OS_DEFINE_H_

#include <stdlib.h>
#include <stdint.h>
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

#endif // OS_DEFINE_H_

