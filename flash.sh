#!/bin/bash
# openvela STM32F103ZET6 烧录脚本
# 用法: chmod +x flash.sh && ./flash.sh

set -e

WORKSPACE_DIR="$HOME/openvela-workspace"
FIRMWARE="$WORKSPACE_DIR/nuttx.bin"
FLASH_ADDR="0x08000000"

echo "=========================================="
echo " 烧录 openvela 到 STM32F103ZET6"
echo "=========================================="

# 检查固件
if [ ! -f "$FIRMWARE" ]; then
    echo "错误: 固件文件不存在: $FIRMWARE"
    echo "请先运行 build_firmware.sh 编译固件"
    exit 1
fi

# 检查 st-flash
if ! command -v st-flash &> /dev/null; then
    echo "错误: st-flash 未安装"
    echo "请运行: sudo apt install stlink-tools"
    exit 1
fi

# 检查 ST-Link 连接
echo "检查 ST-Link 连接..."
if ! st-info --probe &> /dev/null; then
    echo "错误: 未检测到 ST-Link"
    echo "请检查:"
    echo "  1. ST-Link 是否已连接到电脑"
    echo "  2. ST-Link 是否已连接到开发板的 SWD 接口"
    echo "  3. 开发板是否已上电"
    exit 1
fi

echo "ST-Link 已连接"
echo "固件: $FIRMWARE"
echo "Flash 地址: $FLASH_ADDR"
echo ""

# 烧录
echo "开始烧录..."
st-flash write "$FIRMWARE" "$FLASH_ADDR"

echo ""
echo "=========================================="
echo " 烧录完成！"
echo "=========================================="
echo ""
echo "下一步:"
echo "1. 连接 USART1 (PA9/PA10) 到 USB-UART 适配器"
echo "2. 打开串口终端 (115200, 8N1)"
echo "3. 按复位按钮或重新上电"
echo "4. 应看到 'nsh>' 提示符"
echo ""
