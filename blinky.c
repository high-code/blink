/*
   Blink LED connected to GPIO2 example
*/
#include "ets_sys.h"
#include "user_interface.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "driver/uart.h"

static const int pin = 2;
static volatile os_timer_t some_timer;

void some_timerfunc(void *arg)
{
  if(GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << pin))
  {
    os_printf("set high signal level");
    gpio_output_set(0, (1 << pin), 0, 0);
  }
  else
  {
    os_printf("set low signal level");
    gpio_output_set((1 << pin),0, 0, 0);
  }

  //periodically write to uart
  os_printf("SDK version: %s\n", system_get_sdk_version());
  os_printf("CPU frequency: %u\n", system_get_cpu_freq());
  system_print_meminfo();
}

void ICACHE_FLASH_ATTR user_init() {

    gpio_init();
    uart_init(BIT_RATE_115200, BIT_RATE_115200);
    system_set_os_print(0x01);
    wifi_set_opmode(0x02);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    gpio_output_set(0, 0, (1 << pin), 0);
   // setup timer (500ms, repeating)
    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
    os_timer_arm(&some_timer, 5000, 1);
}
