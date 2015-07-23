#ifndef OS_CHUNK_WRITER_H_
#define OS_CHUNK_WRITER_H_

#include "os_define.h"

OS_CPP_START

struct OSChunkWriter;

struct OSIAllocator;
struct OSICWCallback;

typedef void (*os_cw_sync_callback_fp) (struct OSICWCallback *self, const int64_t timestamp);

struct OSICWCallback
{
  os_cw_sync_callback_fp on_sync_succ_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

struct OSChunkWriter *os_cw_init(
    const int fd,
    const int64_t max_data_size,
    const int64_t max_index_count,
    struct OSIAllocator *allocator);

void os_cw_destroy(
    struct OSChunkWriter *ptr);

int os_cw_append(
    struct OSChunkWriter *ptr,
    const char *buffer,
    const int64_t length,
    struct OSICWCallback *callback);

int os_cw_sync(
    struct OSChunkWriter *ptr);

OS_CPP_END

#endif // OS_CHUNK_WRITER_H_

