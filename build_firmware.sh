#!/bin/bash
# openvela STM32F103ZET6 编译脚本
# 用法: chmod +x build.sh && ./build.sh

set -e

WORKSPACE_DIR="$HOME/openvela-workspace"
BOARD_CONFIG="contest2026_316_board:nsh"

echo "=========================================="
echo " 编译 openvela for STM32F103ZET6"
echo "=========================================="

# 检查工作区
if [ ! -d "$WORKSPACE_DIR" ]; then
    echo "错误: 工作区不存在: $WORKSPACE_DIR"
    echo "请先运行 setup_openvela.sh 同步源码"
    exit 1
fi

cd "$WORKSPACE_DIR"

# 检查 build.sh
if [ ! -f "build.sh" ]; then
    echo "错误: build.sh 不存在"
    echo "请确保 repo sync 完成"
    exit 1
fi

echo "编译配置: $BOARD_CONFIG"
echo "开始编译..."
echo ""

# 编译
./build.sh $BOARD_CONFIG -j$(nproc)

echo ""
echo "=========================================="
echo " 编译完成！"
echo "=========================================="
echo ""
echo "固件位置:"
echo "  ELF: $WORKSPACE_DIR/nuttx"
echo "  BIN: $WORKSPACE_DIR/nuttx.bin"
echo "  HEX: $WORKSPACE_DIR/nuttx.hex"
echo ""
echo "烧录命令:"
echo "  st-flash write nuttx.bin 0x08000000"
echo ""
