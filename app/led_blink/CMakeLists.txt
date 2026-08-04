# LED Blink Demo Application
if(CONFIG_APP_LEDBLINK)
  nuttx_add_application(
    NAME led_blink
    PRIORITY 100
    STACKSIZE 2048
    MAIN led_blink_main.c
  )
endif()
