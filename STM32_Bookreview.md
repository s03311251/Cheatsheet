# PC13 - PC15 3mA only
For STM32F1, STM32F4, ???


5.1.2 Battery backup domain

Due to the fact that the switch only sinks a limited amount of current (3 mA), the use of
GPIOs PC13 to PC15 in output mode is restricted: the speed has to be limited to 2 MHz with
a maximum load of 30 pF and these IOs must not be used as a current source (e.g. to drive
a LED).
