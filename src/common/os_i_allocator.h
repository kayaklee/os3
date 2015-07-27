#ifndef OS_I_ALLOCATOR_H_
#define OS_I_ALLOCATOR_H_

#include "os_define.h"

OS_CPP_START

struct OSIAllocator;

typedef void *(*os_i_allocator_alloc) (struct OSIAllocator *self, const int64_t size);
typedef void (*os_i_allocator_free) (struct OSIAllocator *self, void *ptr);
typedef void (*os_i_allocator_reuse) (struct OSIAllocator *self);
typedef void (*os_i_allocator_reset) (struct OSIAllocator *self);

struct OSIAllocator
{
  os_i_allocator_alloc alloc;
  os_i_allocator_free free;
  os_i_allocator_reuse reuse;
  os_i_allocator_reset reset;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

struct OSDefaultAllocator
{
  struct OSIAllocator vt_;
};

struct OSDefaultAllocator g_default_allocator;

OS_CPP_END

#endif // OS_I_ALLOCATOR_H_

