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
  struct OSPAPage *head_;
  struct OSPAPage *curr_;
  int64_t cnt_;
  int64_t used_;
  int64_t total_;
};

OS_CPP_END

#endif // OS_PAGE_ARENA_H_

