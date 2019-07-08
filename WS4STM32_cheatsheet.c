/*----- Install -----*/
// http://www.openstm32.org/Installing%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Bfrom%2BEclipse

// Help -> Install New Software -> Available Software -> Add -> http://ac6-tools.com/Eclipse-updates/org.openstm32.system-workbench.update-site-v2



/*----- Can't %f in printf() -----*/
// http://www.openstm32.org/forumthread2108
// Add linker flags:
// project properties -> C/C++ Build -> Setings -> Tool Settings (TAB) -> MCU GCC Linker -> Miscellaneous -> Linker flags
// if you are using nanolib “-specs=nano.specs” you need to add “-u _printf_float” to enable float printf
// should be something like "-specs=nosys.specs -specs=nano.specs -u _printf_float"
// it takes fucking long to open C/C++ Build Setings



/*----- No HSE in STM32CubeMX Clock Configuration -----*/
// Pinout & Configuration -> System Core -> RCC
