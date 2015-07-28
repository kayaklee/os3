#include <string.h>
#include <stdio.h>
#include "os_page_arena.h"
#include "os_utility.h"

struct OSPAPage
{
  struct OSPAPage *next_;
  int32_t size_;
  int32_t pos_;
  char buf_[0];
};

static struct OSPAPage *get_page_(
    struct OSPageArena *self,
    const int64_t size)
{
  struct OSPAPage *ret = NULL;
  if (NULL == self) {
    // not init
  } else if (size > self->page_size_) {
    // special page
    int64_t alloc_size = size + sizeof(*ret);
    ret = (struct OSPAPage *)(self->allocator_->alloc(self->allocator_, alloc_size));
    if (NULL != ret) {
      ret->next_ = self->special_using_list_;
      self->special_using_list_ = ret;
      ret->size_ = size;
      ret->pos_ = 0;
      self->total_ += alloc_size;
    }
  } else {
    if (NULL != (ret = self->normal_using_list_)
        && size > (self->page_size_ - ret->pos_)) {
      ret = NULL;
    }
    if (NULL == ret) {
      if (NULL != (ret = self->free_list_)) {
        self->free_list_ = ret->next_;
      } else {
        int64_t alloc_size = self->page_size_ = sizeof(*ret);
        ret = (struct OSPAPage *)(self->allocator_->alloc(self->allocator_, alloc_size));
        if (NULL != ret) {
          self->total_ += alloc_size;
        }
      }
      if (NULL != ret) {
        ret->next_ = self->normal_using_list_;
        self->normal_using_list_ = ret;
        ret->size_ = self->page_size_;
        ret->pos_ = 0;
      }
    }
  }
  return ret;
}

static void *alloc_from_page_(
    struct OSPageArena *self,
    struct OSPAPage *page,
    const int64_t size)
{
  void *ret = NULL;
  if (NULL == self
      || NULL == page) {
    // invalid param
  } else if (size > (page->size_ - page->pos_)) {
    // invalid param
  } else {
    ret = page->buf_ + page->pos_;
    page->pos_ += size;
    self->cnt_ += 1;
    self->used_ += size;
  }
  return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

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
    self->allocator_ = (NULL == allocator) ? get_g_default_allocator() : allocator;
    self->page_size_ = page_size;
    self->free_list_ = NULL;
    self->normal_using_list_ = NULL;
    self->special_using_list_ = NULL;
    self->cnt_ = 0;
    self->used_ = 0;
    self->total_ = 0;
  }
  return ret;
}

void os_pa_destroy(
    struct OSPageArena *self)
{
  if (NULL == self) {
    // not init
  } else {
    os_pa_reset(self);
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
    ret = alloc_from_page_(self, page, size);
  }
  return ret;
}

void os_pa_reuse(
    struct OSPageArena *self)
{
  if (NULL == self) {
    // not init
  } else {
    struct OSPAPage *page = self->special_using_list_;
    while (NULL != page) {
      struct OSPAPage *next = page->next_;
      self->total_ -= (page->size_ + sizeof(*page));
      self->allocator_->free(self->allocator_, page);
      page = next;
    }
    self->special_using_list_ = NULL;

    page = self->normal_using_list_;
    while (NULL != page) {
      struct OSPAPage *next = page->next_;
      page->next_ = self->free_list_;
      self->free_list_ = page->next_;
      page = next;
    }
    self->normal_using_list_ = NULL;

    self->cnt_ = 0;
    self->used_ = 0;
  }
}

void os_pa_reset(
    struct OSPageArena *self)
{
  if (NULL == self) {
    // not init
  } else {
    if (NULL != self->allocator_) {
      struct OSPAPage *page = self->free_list_;
      while (NULL != page) {
        struct OSPAPage *next = page->next_;
        self->allocator_->free(self->allocator_, page);
        page = next;
      }
      self->free_list_ = NULL;

      page = self->normal_using_list_;
      while (NULL != page) {
        struct OSPAPage *next = page->next_;
        self->allocator_->free(self->allocator_, page);
        page = next;
      }
      self->normal_using_list_ = NULL;

      page = self->special_using_list_;
      while (NULL != page) {
        struct OSPAPage *next = page->next_;
        self->allocator_->free(self->allocator_, page);
        page = next;
      }
      self->special_using_list_ = NULL;
    }

    self->cnt_ = 0;
    self->used_ = 0;
    self->total_ = 0;
  }
}

const char *os_pa_to_cstring(
    struct OSPageArena *self)
{
  char *ret = os_tc_log_buffer();
  if (NULL == self) {
    snprintf(ret, OS_TC_LOG_BUFFER_SIZE, "nil");
  } else {
    snprintf(ret, OS_TC_LOG_BUFFER_SIZE,
        "this=%p "
        "allocator=%p "
        "page_size=%ld "
        "free_list=%p normal_using_list=%p special_using_list=%p "
        "cnt=%ld used=%ld total=%ld",
        self,
        self->allocator_,
        self->page_size_,
        self->free_list_, self->normal_using_list_, self->special_using_list_,
        self->cnt_, self->used_, self->total_);
  }
  return ret;
}

