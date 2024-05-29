# Controller for Robots

## Overview
This program integrates hardware control with image processing to steer a robot based on visual markers and color detection. The robot uses a camera to detect Aruco markers and led towers, adjusts it's LED colors, and steers based on the processed visual inputs. Communication with the hardware is managed via a serial interface. All this is to implement empathetic behavior in reaching the marker.

## How to run

To run this program, `Raspberry Pi Zero 2 W` single board computer equiped with `Raspberry Pi Camera V3`is required, along with the robot's motorized lower section.

1. PI operating system: Raspberry Pi OS Lite (64-bit), a port of debian Bookworm
    - Download and open Raspberry Pi Imager from the Raspberry Pi website.
    - Choose `Raspberry Pi OS Lite (64-bit)`.
    - Select your SD card and click `WRITE`.
    - *(Optional)* Configure WiFi, change username and password.
    - Once complete, insert the SD card into your Raspberry Pi and power it on.

2. Update package lists and upgrade already installed packages:
```
sudo apt-get update
sudo apt-get upgrade
```

3. Change size of swap on the`Raspberry Pi Zero 2 W`, which has limited RAM:
    - Edit file `/etc/dphys-swapfile` to increase swap size to `2048 mb`
    - Restart computer `sudo reboot`

4. Enable the serial interface on the Raspberry Pi to communicate with motors controlled by the STM32 microcontroller in the lower part of the robot. Use `raspi-config` to configure the settings.

5. Install necessary system packages:
```
sudo apt-get install curl git python3 python3-pip python3-venv python3-libcamera btop tmux libpcap-dev python3-full
sudo apt-get install python3-picamera2 --no-install-recommends
```

6. Create Python's virtual environment:
```
python3 -m venv --system-site-packages VENV
```
Note parameter `--system-site-packages`

7. Using freshly created venv, install modules:
```
VENV/bin/python3 -m pip install adafruit-circuitpython-neopixel pyserial opencv-contrib-python
```

8. Part of code that controls LEDs: `WS2812b` require low level access to procesor registers, therefore it needs sudo access. Because of that, LEDs are controlled by separate program that communicate through socket (`AF_UNIX` type for interprocess communication in unix-like systems). To run LED server:
```
sudo VENV/bin/python neo_server.py
```

9. Application is ready to run:
```
VENV/bin/python3 main.py
```