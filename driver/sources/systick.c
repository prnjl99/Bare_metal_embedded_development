#include "common.h"
#include "systick.h"

// t: expiration time, prd: period, now: current time. Return true if expired
bool timer_expired(uint32_t *timer, uint32_t prd, uint32_t intr_ticks)
{
	if(intr_ticks + prd < *timer)
	{
		*timer = 0UL;                    // Time wrapped? Reset timer
	}
	if(*timer == 0UL)
	{
		*timer = intr_ticks + prd;                   // First poll? Set expiration
	}
	if(*timer > intr_ticks)
	{
		return false;                    // Not expired yet, return
	}

	*timer = ((intr_ticks - *timer) > prd) ? (intr_ticks + prd) : (*timer + prd);  // Next expiration time

	return true;                                   // Expired, return true
}
