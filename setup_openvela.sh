#!/bin/bash
# openvela STM32F103ZET6 编译环境配置脚本
# 用法: chmod +x setup_openvela.sh && ./setup_openvela.sh

set -e

echo "=========================================="
echo " openvela STM32F103ZET6 编译环境配置"
echo "=========================================="

# 1. 更新系统
echo "[1/5] 更新系统包..."
sudo apt update && sudo apt upgrade -y

# 2. 安装编译工具
echo "[2/5] 安装编译工具..."
sudo apt install -y \
    build-essential \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    git \
    curl \
    wget \
    stlink-tools

# 3. 安装 repo 工具
echo "[3/5] 安装 repo 工具..."
mkdir -p ~/.bin
curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo
chmod a+x ~/.bin/repo

# 添加到 PATH
if ! grep -q 'HOME/.bin' ~/.bashrc; then
    echo 'export PATH="$HOME/.bin:$PATH"' >> ~/.bashrc
fi
export PATH="$HOME/.bin:$PATH"

# 4. 验证安装
echo "[4/5] 验证安装..."
echo ""
echo "已安装工具版本:"
arm-none-eabi-gcc --version | head -1
cmake --version | head -1
ninja --version
python3 --version
git --version
repo --version | head -1
st-flash --version | head -1
echo ""

# 5. 同步 openvela 源码
echo "[5/5] 同步 openvela 源码..."
echo ""
read -p "是否现在同步 openvela 源码？(需要较长时间) [y/N]: " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    mkdir -p ~/openvela-workspace
    cd ~/openvela-workspace
    
    echo "初始化 repo..."
    repo init -u https://github.com/open-vela/contest2026_316_famous \
        -b dev-ai-contest-2026 -m contest2026_316_famous.xml
    
    echo "同步源码 (这可能需要 30-60 分钟)..."
    repo sync -c -j8
    
    echo ""
    echo "源码同步完成！"
    echo "工作区位置: ~/openvela-workspace"
fi

echo ""
echo "=========================================="
echo " 环境配置完成！"
echo "=========================================="
echo ""
echo "下一步:"
echo "1. 进入工作区: cd ~/openvela-workspace"
echo "2. 编译固件: ./build.sh contest2026_316_board:nsh -j8"
echo "3. 烧录: st-flash write nuttx.bin 0x08000000"
echo ""
