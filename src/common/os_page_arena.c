#include <string.h>
#include "os_page_arena.h"

struct OSPAPage
{
  struct OSPAPage *next_;
  int32_t size_;
  int32_t pos_;
  char buf_[0];
};

struct OSPAPage *get_page_(
    struct OSPageArena *self,
    const int64_t size)
{
  struct OSPAPage *ret = NULL;
  if (NULL == self) {
    // not init
  } else {
  }
  return ret;
}

int os_pa_init(
    struct OSPageArena *self,
    const int64_t page_size,
    struct OSIAllocator *allocator)
{
  int ret = OS_SUCCESS;
  if (NULL == self) {
    ret = OS_INVALID_PARAM;
  } else if (0 >= page_size
      || INT32_MAX < page_size) {
    ret = OS_INVALID_PARAM;
  } else {
    self->allocator_ = (NULL == allocator) ?
      (struct OSIAllocator*)&g_default_allocator : allocator;
    self->page_size_ = page_size;
    self->head_ = NULL;
    self->curr_ = NULL;
    self->cnt_ = 0;
    self->used_ = 0;
    self->total_ = 0;
  }
  return ret;
}

void os_pa_destroy(
    struct OSPageArena *self)
{
  if (NULL != self) {
    if (NULL != self->allocator_) {
      struct OSPAPage *page = self->head_;
      while (NULL != page) {
        struct OSPAPage *next = page->next_;
        self->allocator_->free_(self->allocator_, page);
        page = next;
      }
    }
    memset(self, 0, sizeof(*self));
  }
}

void *os_pa_alloc(
    struct OSPageArena *self,
    const int64_t size)
{
  void *ret = NULL;
  struct OSPAPage *page = NULL;
  if (NULL == self
      || 0 >= size) {
    // invalid param
  } else if (NULL == (page = get_page_(self, size))) {
    // allocate page fail
  } else {
    //ret = alloc_from_page_(self, page, size);
  }
  return ret;
}

void os_pa_reuse(
    struct OSPageArena *self)
{
}

void os_pa_reset(
    struct OSPageArena *self)
{
}

const char *to_cstring(
    struct OSPageArena *self)
{
}

