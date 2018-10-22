# How to ESP32 with Arduino on MAC:


## Download and install USB Driver
You will need USB-to-UART-Bridge drivers in order to be able to choose the ESP-32 port inside Arudino and upload code. Download and install the drivers from:  https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers


## Setup Arduino IDE
We need to install additional Arduino IDE drivers and examples files to run the boards.
1. Open Arudino IDE
2. Open Preferences > Settings.
3. Update field `Additional Boards Manager URLs` to `http://arduino.esp8266.com/stable/package_esp8266com_index.json`.

![Screenshot](screenshot_arduino.png)

4. Press `Ok`
5. Restart Arduino IDE
6. Under `Tools > Board` choose your board type `ESP32 Dev Module`
7. Choose port `/dev/cu.SLAB_USBtoUART`


## Troubleshoot
Follow installation instruction here:
https://github.com/espressif/arduino-esp32#installation-instructions

### Short version

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
