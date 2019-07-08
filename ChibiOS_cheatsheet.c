// sudo st-flash write ch.bin 0x8000000

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

/*
 * Green LED blinker thread, times are in milliseconds.
 */

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

	(void)arg;
	chRegSetThreadName("blinker");
	while (true) {
		palClearPad(GPIOA, GPIOA_LED_GREEN);
		chThdSleepMilliseconds(500);
		palSetPad(GPIOA, GPIOA_LED_GREEN);
		chThdSleepMilliseconds(500);
	}
}

/*
 * Application entry point.
 */
int main(void) {

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	/*
	 * Activates the serial driver 2 using the driver default configuration.
	 */
	sdStart(&SD2, NULL);

	/*
	 * Creates the blinker thread.
	 */
	chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */
	while (true) {
		if (!palReadPad(GPIOC, GPIOC_BUTTON))
			test_execute((BaseSequentialStream *)&SD2);
		chThdSleepMilliseconds(10000);
	}
}



/*----------Create Thread----------*/
// http://www.chibios.org/dokuwiki/doku.php?id=chibios:howtos:createthread

// chSysInit() creates 2 threads: idle thread & main thread
// Idle thread: lowest priority, usually switched the sys in low power mode
// Main thread: NORMALPRIO priority, executes at startup

// # Static VS Dynamic
// ## Static Thread: allocated in memory at compile time
// memory cannot be reused, usually for safety applications

// reserves 128 bytes of stack for the thread
static THD_WORKING_AREA(myThreadWorkingArea, 128);

// create
// thread_t *tp = chThdCreateStatic()
chThdCreateStatic(myThreadWorkingArea,
                  sizeof(myThreadWorkingArea),
                  NORMALPRIO,  /* Initial priority.    */
                  myThread,    /* Thread function.     */
                  NULL);       /* Thread parameter.    */

// e.g.
#include <ch.h>

static THD_WORKING_AREA(myThreadWorkingArea, 128);

static THD_FUNCTION(myThread, arg) {
	while (true) {
		LED_ON();
		chThdSleepMilliseconds(500);
		LED_OFF();
		chThdSleepMilliseconds(500);
	}
}

int main(int argc, char *argv[]) {
	/* Starting the flashing LEDs thread.*/
	(void)chThdCreateStatic(myThreadWorkingArea, sizeof(myThreadWorkingArea), NORMALPRIO, myThread, NULL);
	.
	.
	.
}


// ## Dynamic Thread: created at run time

// create using heap allocator
thread_t *tp = chThdCreateFromHeap(NULL,          /* NULL = Default heap. */
                                   THD_WORKING_AREA_SIZE(128), /* Stack.  */
                                   NORMALPRIO,    /* Initial priority.    */
                                   myThread,      /* Thread function.     */
                                   NULL);         /* Thread parameter.    */

// e.g.
#include <ch.h>

static THD_FUNCTION(myThread, arg) {
	unsigned i = 10;
	while (i > 0) {
		LED_ON();
		chThdSleepMilliseconds(500);
		LED_OFF();
		chThdSleepMilliseconds(500);
		i--;
	}
	chthdExit((msg_t)i);
}
 
int main(int argc, char *argv[]) {
 
	thread_t *tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(128), NORMALPRIO+1, myThread, NULL);
	if (tp == NULL)
		chSysHalt("out of memory");
 
	/* The main thread continues its normal execution.*/
	.
	.
	/*
	 * Now waits for the spawned thread to terminate (if it has not terminated
	 * already) then gets the thread exit message (msg) and returns the
	 * terminated thread memory to the heap (default system heap in this
	 * example).
	 */
	msg_t msg = chThdWait(tp);
	.
	.
}

// create using pool allocator
// e.g.
#include <ch.h>

static THD_FUNCTION(myThread, arg) {

	unsigned i = 10;
	while (i > 0) {
		LED_ON();
		chThdSleepMilliseconds(500);
		LED_OFF();
		chThdSleepMilliseconds(500);
		i--;
	}
	chthdExit((msg_t)i);
}
 
int main(int argc, char *argv[]) {
 
	thread_t *tp = chThdCreateFromMemoryPool(myPool, NORMALPRIO+1, myThread, NULL);
	if (tp == NULL)
		chSysHalt("pool empty");
 
	/* The main thread continues its normal execution.*/
	.
	.
	/*
	 * Now waits for the spawned thread to terminate (if it has not terminated
	 * already) then gets the thread exit message (msg) and returns the
	 * terminated thread memory to the original memory pool.
	 */
	msg_t msg = chThdWait(tp);
	.
	.
}

// sleep
// perform a context switch resuming the thread in ready state having the highest priority
chThdSleep()



/*----------GPIO----------*/
// http://www.playembedded.org/blog/en/2015/02/10/hello-chibios/

// # Set mode
	palSetPadMode(GPIOC, GPIOC_PIN0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
// PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST is bitwise or
// Generic modes:
//    PAL_MODE_RESET
//    PAL_MODE_UNCONNECTED
//    PAL_MODE_INPUT: floating
//    PAL_MODE_INPUT_PULLUP
//    PAL_MODE_INPUT_PULLDOWN
//    PAL_MODE_INPUT_ANALOG
//    PAL_MODE_OUTPUT_PUSHPULL
//    PAL_MODE_OUTPUT_OPENDRAIN

// Usually, PAL driver already enable in halconf.h
/**
 * @brief   Enables the PAL subsystem.
 */
#if !defined(HAL_USE_PAL) || defined(__DOXYGEN__)
#define HAL_USE_PAL                 TRUE
#endif

// More pin settings -> board.h & board.c
// http://www.playembedded.org/blog/en/2015/07/31/port-a-chibios-based-application-to-another-platform/

// # Read
	palReadPad() // reads pin status returning PAL_LOW or PAL_HIGH

// # Write
	palWritePad() // set output as PAL_LOW or PAL_HIGH
	palSetPad() // writes output value to PAL_HIGH
	palClearPad() // writes output value to PAL_LOW
	palTogglePad() // inverts output value.

// e.g. If button clicked, toggle the LED
static THD_WORKING_AREA(waThd1, 128);
static THD_FUNCTION(Thd1, arg) {

	(void) arg;
	chRegSetThreadName("Button Check");

	while (TRUE) {
		/*
		 * Checking if button is pressed
		 */
		if (palReadPad(GPIOC, GPIOC_BUTTON)) {
			chThdSleepMilliseconds(50);
			/*
			 * Checking if button is released
			 */
			if (!palReadPad(GPIOC, GPIOC_BUTTON)) {
				/*
				 * At that point we could assert that button has been pushed.
				 * We raise a flag
				 */
				button_pressed = TRUE;
			}
		}
		chThdSleepMilliseconds(1);
	}
}

static THD_WORKING_AREA(waThd2, 128);
static THD_FUNCTION(Thd2, arg) {

	(void) arg;
	chRegSetThreadName("Led handler");

	while (TRUE) {
		if (button_pressed) {
			/*
			 * Toggoling LED status
			 */
			palTogglePad(GPIOA, GPIOA_LED_GREEN);
			/*
			 * Lowering the flag
			 */
			button_pressed = FALSE;
		}
		chThdSleepMilliseconds(10);
	}
}

int main(void) {
	halInit();
	chSysInit();

	chThdCreateStatic(waThd1, sizeof(waThd1), NORMALPRIO + 1, Thd1, NULL);
	chThdCreateStatic(waThd2, sizeof(waThd2), NORMALPRIO - 1, Thd2, NULL);

	while (TRUE) {
		chThdSleepMilliseconds(500);
	}
}



/*----------chprintf()----------*/
// http://www.playembedded.org/blog/en/2015/02/10/hello-chibios/
// this example uses Serial Driver

#include "chprintf.h"
BaseSequentialStream* chp = (BaseSequentialStream*) &SD2;
...
int main(){
	halInit();
	chSysInit();
...
	sdStart(&SD2, NULL);
	while(TRUE) {
		chprintf(chp, "Hello world\n\r");

// halconf.h
/**
 * @brief   Enables the SERIAL subsystem.
 */
#if !defined(HAL_USE_SERIAL) || defined(__DOXYGEN__)
#define HAL_USE_SERIAL              TRUE
#endif

// mcuconf.h
// enable Serial Driver 2, which is used in BaseSequentialStream* chp = (BaseSequentialStream*) &SD2;

/*
 * UART driver system settings.
 */
#define STM32_UART_USE_USART1               FALSE
#define STM32_UART_USE_USART2               TRUE
#define STM32_UART_USE_USART6               FALSE

// Makefile
// chprintf() requires chprintf.c, memstreams.c and related headers

CHIBIOS = ../../chibios3
...
# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(STARTUPSRC) \
       $(KERNSRC) \
       $(PORTSRC) \
       $(OSALSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(TESTSRC) \
       $(CHIBIOS)/os/hal/lib/streams/memstreams.c \
       $(CHIBIOS)/os/hal/lib/streams/chprintf.c \
       main.c
...
INCDIR = $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(CHIBIOS)/os/hal/lib/streams \
         $(CHIBIOS)/os/various
...



/*----------SerialPeripheral Interface(SPI)----------*/
// http://www.playembedded.org/blog/en/2015/02/15/meeting-spi/



/*----------PWM----------*/
// http://www.playembedded.org/blog/en/2015/02/16/sampling-and-dimming/

// halconf.h
#define HAL_USE_PWM                 TRUE

// mcuconf.h
#define STM32_PWM_USE_TIM1                  TRUE

static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  if(percentage)
    palSetPad(GPIOA, GPIOA_LED_GREEN);
}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  palClearPad(GPIOA, GPIOA_LED_GREEN);
}

static PWMConfig pwmcfg = {
  1000000,         /* 1MHz PWM clock frequency. */
  10000,           /* Initial PWM period = 10000/1000000 = 0.01s = 10ms. */
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
  0
};

static THD_WORKING_AREA(waThread1, 256);
static THD_FUNCTION(Thread1, arg) {

	(void) arg;
	chRegSetThreadName("Led handler");
	pwmStart(&PWMD1, &pwmcfg);

//	pwmEnableChannel(&PWMD1, 0, 5000); // in term of tick
	pwmEnableChannel(&PWMD1, 0, PWM_FRACTION_TO_WIDTH(&PWMD1, 2, 1)); // 50%

	pwmEnableChannelNotification(&PWMD1, 0);// Enables a channel de-activation edge notification
	pwmEnablePeriodicNotification(&PWMD1);// Enables the periodic activation edge notification

	chThdSleepMilliseconds(5000);

	pwmChangePeriod(&PWMD1, 2000); // period = 2000 ticks = 200 ms
	pwmEnableChannel(&PWMD1, 0, PWM_FRACTION_TO_WIDTH(&PWMD1, 2, 1)); // have to change again

	chThdSleepMilliseconds(5000);

	pwmDisableChannel(&PWMD1, 0);

}







/*----------Henry talking about board.h----------*/
/*
1. check which pin can do which <- Cube MX
2. Set board.h attribute, OTYPE, PUPDR, AR (Alternate f(x))
3. Use it
*/
