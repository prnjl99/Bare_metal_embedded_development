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

/*#define find_size(arg) ((arg)

find_size_func(*/

int main(void)
{
	int size=sizeof(int);
	int size1=sizeof(size);
    int *ptr1 = (int*)malloc(size);
    int *ptr2 = (int*)malloc(size);
    int *ptr3 = (int*)malloc(size);
    int *ptr4 = (int*)malloc(size);
    int *ptr5 = (int*)malloc(size);
    int *ptr6 = (int*)malloc(size);
    int *ptr7 = (int*)malloc(size);
    int *ptr8 = (int*)malloc(size);
    int *ptr9 = (int*)malloc(size);
    int *ptr10 = (int*)malloc(size);
    int *ptr11 = (int*)malloc(size);
    int *ptr12 = (int*)malloc(size);
    int *ptr13 = (int*)malloc(size);
    int *ptr14 = (int*)malloc(size);
    int *ptr15 = (int*)malloc(size);
    int *ptr16 = (int*)malloc(size);
    int *ptr17 = (int*)malloc(size);
    int *ptr18 = (int*)malloc(size);
    int *ptr19 = (int*)malloc(size);
    int *ptr20 = (int*)malloc(size1);

	*ptr1 = 0x12345678;
	*ptr2 = 0x87654321;
	*ptr3 = 0x12345678;
	*ptr4 = 0x87654321;
	*ptr5 = 0x12345678;
	*ptr6 = 0x87654321;
	*ptr7 = 0x12345678;
	*ptr8 = 0x87654321;
	*ptr9 = 0x12345678;
	*ptr10 = 0x87654321;
	*ptr11 = 0x12345678;
	*ptr12 = 0x87654321;
	*ptr13 = 0x12345678;
	*ptr14 = 0x87654321;
	*ptr15 = 0x12345678;
	*ptr16 = 0x87654321;
	*ptr17 = 0x12345678;
	*ptr18 = 0x87654321;
	*ptr19 = 0x12345678;
	*ptr20 = 0x87654321;

    if((ptr20 != NULL) && (ptr19 != NULL) && (ptr18 != NULL) && (ptr17 != NULL) && (ptr16 != NULL) && (ptr15 != NULL) && (ptr14 != NULL) && (ptr13 != NULL) && (ptr12 != NULL) && (ptr11 != NULL) && (ptr10 != NULL) && (ptr9 != NULL) && (ptr8 != NULL) && (ptr7 != NULL) && (ptr6 != NULL) && (ptr5 != NULL) && (ptr4 != NULL) && (ptr3 != NULL) && (ptr2 != NULL) && (ptr1 != NULL))
    {
        toggle_LED();
    }
}

void User_intr_handler(void)
{
    while(1){};
}

