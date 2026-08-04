# Contest 2026 team 316 - STM32F103ZET6 Board Source
nuttx_add_library(board)
target_sources(board PRIVATE 
  board_boot.c
  stm32_gpio.c
  stm32_spi.c
  stm32_i2c.c
)
