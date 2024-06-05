### EMPATHETIC
The project involves creating a control system for a two-wheeled robot using an STM32 microcontroller. The code handles four main components: motors, encoders, laser sensor and uart communication:

1. **Motors**: The STM32 microcontroller controls two DC motors using the DRV8833 motor driver. Pulse Width Modulation (PWM) is used to manage the speed and direction of the motors. The motors are controlled using a PID controller with an IIR filter for precise speed regulation and stability. The code includes functions for initializing PWM and adjusting motor parameters in real time.

2. **Encoders**: Each motor is equipped with a Hall-effect encoder that provides information about the speed and angular position of the wheels. The microcontroller receives signals from the encoders and converts them into speed and distance values. This data is used for precise movement control and to maintain a closed-loop feedback system.

3. **Laser Sensor**: The robot uses the VL53L0X laser sensor to detect obstacles and measure distances from objects. The project utilizes the ST library for handling the VL53L0X sensor. The data from the laser sensor is processed by the microcontroller, allowing the robot to avoid obstacles.

4. **UART Communication**: The program receives the desired speed information for each motor via UART, in the format 'LSXYZRSXYZ', where L stands for the left motor, R stands for the right motor, S is the sign (+ for positive, - for negative), and XYZ is the speed in rad/s, padded with leading zeros to three places. For example, to stop left motor, and spin right motor at 100rad/s, following string is used: 'L+000R+100'. 
UART config: 115200 8n1

The entire system is programmed in C, using the **HAL** (Hardware Abstraction Layer) library to handle the peripherals of the STM32 microcontroller. The code is modular, allowing for easy expansion and modification of individual functions.

CPU: STM32H7A3RITx
IDE: **STM32CubeIDE**, version: *1.15.0*
Dependencies:
- **CMSIS**, version *5.7.0*, (provides the implementation of digital filters): [link to download](https://www.keil.com/pack/ARM.CMSIS.5.7.0.pack)

To install CMSIS, in STM32CubeIDE nagivate to Help -> Manage Embedded Software Packages -> From Local... and select downloaded CMSIS pack.

### L152_ADC
Project mainly focused only on learning and testing stm32 platform
CPU: STM32L152RE
Objective: trigger ADC with TIMER using DMA

GPT-3.5 was used to improve above description