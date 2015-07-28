#include <stdlib.h>
#include "os_i_allocator.h"

struct OSDefaultAllocator
{
  struct OSIAllocator vt_;
};

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
  get_g_default_allocator()->alloc = alloc_;
  get_g_default_allocator()->free = free_;
  get_g_default_allocator()->reuse = reuse_;
  get_g_default_allocator()->reset = reset_;
}

struct OSIAllocator *get_g_default_allocator()
{
  static struct OSDefaultAllocator g_default_allocator;
  return &g_default_allocator.vt_;
}
