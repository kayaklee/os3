#ifndef OS_PAGE_ARENA_H_
#define OS_PAGE_ARENA_H_

#include "os_define.h"
#include "os_i_allocator.h"

OS_CPP_START

struct OSPAPage;

struct OSPageArena
{
  struct OSIAllocator *allocator_;
  int64_t page_size_;
  struct OSPAPage *free_list_;
  struct OSPAPage *normal_using_list_;
  struct OSPAPage *special_using_list_;
  int64_t cnt_;
  int64_t used_;
  int64_t total_;
};

int os_pa_init(
    struct OSPageArena *self,
    const int64_t page_size,
    struct OSIAllocator *allocator);

void os_pa_destroy(
    struct OSPageArena *self);

void *os_pa_alloc(
    struct OSPageArena *self,
    const int64_t size);

void os_pa_reuse(
    struct OSPageArena *self);

void os_pa_reset(
    struct OSPageArena *self);

const char *to_cstring(
    struct OSPageArena *self);

OS_CPP_END

#endif // OS_PAGE_ARENA_H_

