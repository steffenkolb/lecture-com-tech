# How to ESP32 with Arduino on MAC:


## Download and install USB Driver
You will need USB-to-UART-Bridge drivers in order to be able to choose the ESP-32 port inside Arudino and upload code. Download and install the drivers from:  https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

## Download Arduino Driver

1. Follow the instructions on: https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/mac.md

```bash
mkdir -p ~/Documents/Arduino/hardware/espressif && \
cd ~/Documents/Arduino/hardware/espressif && \
git clone https://github.com/espressif/arduino-esp32.git esp32 && \
cd esp32 && \
git submodule update --init --recursive && \
cd tools && \
python get.py
```

2. Open or restart Arduino IDE
3. Open `Tools > Board` and choose `ESP32 Dev Module`
4. For `Tools > Port` choose `/dev/cu.SLAB_USBtoUART`