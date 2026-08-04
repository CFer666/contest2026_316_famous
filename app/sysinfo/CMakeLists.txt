# System Info Demo Application
if(CONFIG_APP_SYSINFO)
  nuttx_add_application(
    NAME sysinfo
    PRIORITY 100
    STACKSIZE 4096
    MAIN sysinfo_main.c
  )
endif()
