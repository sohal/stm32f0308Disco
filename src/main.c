// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "led.h"
#include "usart1.h"

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	led_Init(BLUE);
	led_Init(GREEN);
	led_Init(RED);
//	usart1_Init();
	// Infinite loop
	timer_start();

//	uint8_t hi[] = "hello";
//	usart1_Tx(hi, sizeof(hi));

	while (1)
	{
		led_ON(GREEN);
		led_OFF(BLUE);
		led_OFF(RED);
		timer_sleep(BLINK_ON_TICKS);
		led_OFF(GREEN);
		led_ON(BLUE);
		led_ON(RED);
		timer_sleep(BLINK_OFF_TICKS);
	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
