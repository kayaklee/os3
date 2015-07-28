#include <assert.h>
#include <stdio.h>
#include "common/os_page_arena.h"

extern struct OSDefaultAllocator g_default_allocator;

int main()
{
  struct OSPageArena pa;

  int ret = os_pa_init(&pa, 65536, get_g_default_allocator());
  assert(OS_SUCCESS == ret);

  void *ptr = os_pa_alloc(&pa, 65537);
  assert(NULL != ptr);

  fprintf(stdout, "%s\n", os_pa_to_cstring(&pa));
  return 0;
}
