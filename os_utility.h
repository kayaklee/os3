#ifndef OS_UTILITY_H_
#define OS_UTILITY_H_

#include "os_define.h"

OS_CPP_START

extern int64_t os_get_time();

extern void os_bind_core(int64_t core_id);

OS_CPP_END

#endif // OS_UTILITY_H_

