#include "os_log.h"

static int *os_log_glevel()
{
  static int glevel = INFO;
  return &glevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const char* os_log_print_array(char* buf, int64_t len, int64_t* array, int size)
{
  int64_t pos = 0;
  int64_t count = 0;
  int64_t i = 0;
  for(i = 0; i < size; i++)
  {
    count = snprintf(buf + pos, len - pos, "0x%lx ", array[i]);
    if (count >= 0 && pos + count + 1 < len)
    {
      pos += count;
    }
    else
    {
      PD_LOG(WARN, "buf not enough, len=%ld, array_size=%d", len, size);
      break;
    }
  }
  buf[pos + 1] = 0;
  return buf;
}

const char* os_log_print_bt()
{
  static __thread void *addrs[100];
  static __thread char buf[1024];
  int size = backtrace(addrs, 100);
  return os_log_print_array(buf, sizeof(buf), (int64_t*)addrs, size);
}

void os_log_set_glevel(const int level)
{
  *os_log_glevel() = level;
}

int os_log_get_glevel()
{
  return *os_log_glevel();
}

