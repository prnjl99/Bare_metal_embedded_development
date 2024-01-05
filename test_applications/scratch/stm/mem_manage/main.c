#include <stddef.h>
#include <stdlib.h>

#include "startup.h"
#include "common.h"
#include "gpio.h"

#define HEAP_ALIGNMENT 0x8

void* malloc_int(size_t incr)
{
  extern uint8_t _heap_start;
  extern uint8_t _heap_limit;
  static uint8_t *heap_end;
  uint8_t *temp;

  if(heap_end == 0)
  {
      uint32_t temp = (uint32_t)(&_heap_start);
      /* Ensure heap starts on aligned boundary */
      if((temp & (HEAP_ALIGNMENT-1)) != 0)
      {
          /* If not then add (HEAP_ALIGNMENT-1) and then and with ~HEAP_ALIGNMENT.
          Adding is required because suppose, start is at 0x1001 and alignment is 4.
          Then just ending will make temp less than where it should start. It will become 0x1000.
          But adding will make it 0x1100. */
          temp += (HEAP_ALIGNMENT-1);
          temp &= ~((HEAP_ALIGNMENT-1));
      }

      heap_end = (uint8_t *)temp;
  }

  temp = heap_end + incr;

  if (temp > &_heap_limit)
  {
    return (void *)-1;
  }

  heap_end = temp;
  temp = temp - incr;

  return temp;
}

int main(void)
{
    int *ptr = (int*)malloc_int(sizeof(int));
    int *ptr1 = (int*)malloc_int(50*sizeof(int));
    int *ptr2 = (int*)malloc_int(10*sizeof(int));
    int *ptr3 = (int*)malloc_int(100*sizeof(int));

    if((ptr != NULL) && (ptr1 == NULL) && (ptr2 == NULL) && (ptr3 == NULL))
    {
        toggle_LED();
    }
}

void User_intr_handler(void)
{
    while(1){};
}

