#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#include "startup.h"
#include "common.h"
#include "gpio.h"

void *_sbrk(size_t incr)
{
  extern uint8_t _heap_start;
  extern uint8_t _heap_limit;
  static uint8_t *heap_end;
  uint8_t *temp;

  if(heap_end == 0)
  {
      heap_end = &_heap_start;
  }

  temp = heap_end + incr;

  if (temp > &_heap_limit)
  {
    errno = ENOMEM;
    return (void *)-1;
  }

  heap_end = temp;
  temp = temp - incr;

  return temp;
}

int main(void)
{
    int *ptr = (int*)malloc(sizeof(int));
    int *ptr1 = (int*)malloc(100*sizeof(int));

    if((ptr != NULL) && (ptr1 == NULL))
    {
        toggle_LED();
    }
}

void User_intr_handler(void)
{
    while(1){};
}

