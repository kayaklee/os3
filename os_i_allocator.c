#include <stdlib.h>
#include "os_i_allocator.h"

static void *alloc_(struct OSIAllocator *self, const int64_t size)
{
  UNUSED(self);
  return malloc(size);
}

static void free_(struct OSIAllocator *self, void *ptr)
{
  UNUSED(self);
  return free(ptr);
}

static void reuse_(struct OSIAllocator *self)
{
  UNUSED(self);
}

static void reset_(struct OSIAllocator *self)
{
  UNUSED(self);
}

void  __attribute__((constructor)) init_g_default_allocator()
{
  g_default_allocator.vt_.alloc_ = alloc_;
  g_default_allocator.vt_.free_ = free_;
  g_default_allocator.vt_.reuse_ = reuse_;
  g_default_allocator.vt_.reset_ = reset_;
}
