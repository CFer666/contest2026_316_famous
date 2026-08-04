# Button Test Demo Application
if(CONFIG_APP_BUTTON_TEST)
  nuttx_add_application(
    NAME button_test
    PRIORITY 100
    STACKSIZE 2048
    MAIN button_test_main.c
  )
endif()
