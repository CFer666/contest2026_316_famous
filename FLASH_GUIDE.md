# STM32F103ZET6 烧录说明

## Windows 端烧录方法

### 方法 1: 使用 STM32CubeProgrammer (推荐)

1. **下载 STM32CubeProgrammer**
   - 访问: https://www.st.com/en/development-tools/stm32cubeprog.html
   - 下载并安装 STM32CubeProgrammer

2. **连接 ST-Link**
   - 将 ST-Link V2/V2-1 连接到电脑 USB
   - 将 ST-Link 的 SWD 接口连接到开发板:
     - SWDIO → 开发板 SWDIO
     - SWCLK → 开发板 SWCLK
     - GND → 开发板 GND
     - 3.3V → 开发板 3.3V (如果需要供电)

3. **烧录固件**
   ```powershell
   # 打开 STM32CubeProgrammer CLI
   STM32_Programmer_CLI.exe -c port=SWD -w nuttx.bin 0x08000000 -v -rst
   ```

### 方法 2: 使用 ST-Link Utility

1. **下载 ST-Link Utility**
   - 访问: https://www.st.com/en/development-tools/stsw-link004.html
   - 下载并安装

2. **烧录固件**
   - 打开 ST-Link Utility
   - 连接到目标 (Target → Connect)
   - 加载固件 (File → Open file → 选择 nuttx.bin)
   - 设置起始地址: 0x08000000
   - 烧录 (Target → Program & Verify)

### 方法 3: 使用 OpenOCD

1. **安装 OpenOCD**
   ```powershell
   # 使用 Chocolatey
   choco install openocd -y
   ```

2. **烧录固件**
   ```powershell
   openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program nuttx.bin 0x08000000 verify reset exit"
   ```

## 串口连接

### 硬件连接

将 USB-UART 适配器连接到开发板:

| 开发板 | USB-UART 适配器 |
|--------|-----------------|
| PA9 (USART1_TX) | RX |
| PA10 (USART1_RX) | TX |
| GND | GND |

### 串口终端设置

- **波特率**: 115200
- **数据位**: 8
- **停止位**: 1
- **校验**: 无
- **流控**: 无

推荐串口终端工具:
- PuTTY
- SecureCRT
- MobaXterm
- Arduino IDE 串口监视器
- VS Code Serial Monitor

## 从 Linux VM 复制固件到 Windows

如果在 Linux VM 中编译，需要将固件复制到 Windows:

### 方法 1: 共享文件夹

1. 在 VM 设置中配置共享文件夹
2. 编译后复制固件到共享文件夹:
   ```bash
   cp ~/openvela-workspace/nuttx.bin /mnt/hgfs/shared/
   ```

### 方法 2: SCP/SFTP

1. 在 Windows 中使用 WinSCP 或 FileZilla
2. 连接到 Linux VM
3. 下载固件文件

### 方法 3: 临时 HTTP 服务器

在 Linux VM 中:
```bash
cd ~/openvela-workspace
python3 -m http.server 8080
```

在 Windows 中:
```powershell
# 使用浏览器下载
# 访问 http://<VM-IP>:8080/nuttx.bin

# 或使用 PowerShell
Invoke-WebRequest -Uri "http://<VM-IP>:8080/nuttx.bin" -OutFile "nuttx.bin"
```

## 故障排除

### ST-Link 连接失败

1. 检查 ST-Link 驱动是否安装
2. 检查 SWD 接线是否正确
3. 确认开发板已上电
4. 尝试降低 SWD 频率

### 串口无输出

1. 检查串口接线 (TX/RX 是否交叉)
2. 确认波特率设置为 115200
3. 检查开发板是否正常启动
4. 尝试按复位按钮

### 编译错误

1. 确认所有依赖已安装
2. 检查 ARM 工具链版本
3. 清理并重新编译:
   ```bash
   ./build.sh contest2026_316_board:nsh distclean
   ./build.sh contest2026_316_board:nsh -j8
   ```
