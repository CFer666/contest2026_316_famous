# Application Demos

This directory contains demo applications for STM32F103ZET6 development board.

## Available Demos

### 1. LED Blink Demo (`led_blink`)

**功能**: LED 闪烁演示

**硬件连接**:
- LED1: PB0 (绿色)
- LED2: PB1 (黄色)
- LED3: PB5 (红色)

**使用方法**:
```bash
nsh> led_blink
```

**说明**: 
- 以 500ms 间隔闪烁 LED1
- 可用于验证 GPIO 输出功能
- 按 Ctrl+C 停止

### 2. Button Test Demo (`button_test`)

**功能**: 按键检测演示

**硬件连接**:
- USER 按键: PA0 (低电平有效)

**使用方法**:
```bash
nsh> button_test
```

**说明**:
- 使用 poll 机制检测按键
- 超时时间: 10 秒
- 按下 USER 按键后显示 "Button test PASSED!"
- 可用于验证 GPIO 输入功能

### 3. System Info Demo (`sysinfo`)

**功能**: 系统信息显示

**使用方法**:
```bash
nsh> sysinfo
```

**说明**:
- 显示操作系统版本信息
- 显示硬件规格信息
- 显示可用外设列表
- 显示 LED/按键连接信息
- 显示内存布局信息
- 显示 NSH 命令帮助

## 编译说明

所有 Demo 应用默认启用。如需禁用某个 Demo，可在 defconfig 中添加：

```
# 禁用 LED Blink Demo
# CONFIG_APP_LEDBLINK is not set

# 禁用 Button Test Demo
# CONFIG_APP_BUTTON_TEST is not set

# 禁用 System Info Demo
# CONFIG_APP_SYSINFO is not set
```

## 扩展 Demo

可以在此目录下添加更多 Demo 应用：

1. **SPI Demo** - SPI 通信演示
2. **I2C Demo** - I2C 设备读写演示
3. **ADC Demo** - ADC 采集演示
4. **PWM Demo** - PWM 输出演示
5. **UART Demo** - 多串口通信演示
6. **RTC Demo** - 实时时钟演示
7. **Watchdog Demo** - 看门狗演示

## 目录结构

```
app/
├── CMakeLists.txt          # 应用顶层 CMake
├── README.md               # 本文件
├── led_blink/              # LED 闪烁 Demo
│   ├── CMakeLists.txt
│   ├── Kconfig
│   └── led_blink_main.c
├── button_test/            # 按键检测 Demo
│   ├── CMakeLists.txt
│   ├── Kconfig
│   └── button_test_main.c
└── sysinfo/                # 系统信息 Demo
    ├── CMakeLists.txt
    ├── Kconfig
    └── sysinfo_main.c
```
