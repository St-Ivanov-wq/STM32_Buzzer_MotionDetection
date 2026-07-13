# STM32 Motion Detection System

A lightweight, bare-metal embedded system that utilizes an infrared light barrier to trigger an active piezoelectric buzzer. This project was developed as a laboratory prototype for the Electronic and Medical Instrumentation specialization at the Technical University of Sofia.

## 📌 Project Overview
This system is built around the **STM32F0DISCOVERY** microcontroller. It constantly monitors a digital input from an infrared emitter/receiver pair. When the infrared beam is physically broken, the microcontroller detects the state change and immediately drives a digital output high, sounding an alarm via an active buzzer. 

The firmware is written entirely in C using the **STM32 Hardware Abstraction Layer (HAL)** for maximum efficiency and hardware control.

## 🛠️ Hardware Requirements
* **Microcontroller:** STM32F0DISCOVERY (ARM Cortex-M0)
* **Sensor:** KY-010 Light Barrier (Infrared photo-interrupter)
* **Actuator:** KY-012 Active Piezo-Buzzer
* **Protection:** 1x 100Ω Resistor (Current limiting for the buzzer to balance volume and pin safety)
* Jumper wires & Breadboard

## 🔌 Wiring & Pin Configuration

| Component | STM32 Pin | Logic Level | Notes |
| :--- | :--- | :--- | :--- |
| **KY-010 Sensor** (Signal) | `PC0` | 3.3V | Configured as standard GPIO Input. |
| **KY-012 Buzzer** (Signal) | `PF4` | 3.3V | Configured as Push-Pull Output. **Must be wired in series with the 100Ω resistor** to protect the MCU pin while maintaining a loud tone. |
| **VCC** (Both modules) | `3V3` | 3.3V | Do not use 5V to ensure logic level compatibility. |
| **GND** (Both modules) | `GND` | 0V | Common ground. |

![Wiring Diagram](assets/wiring.jpg)

## 💻 Software & Toolchain
* **Language:** C
* **Framework:** STM32Cube (HAL)
* **Build System:** PlatformIO
* **Compiler:** GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)
* **Debugger/Flasher:** OpenOCD via ST-LINK/V2

## 🚀 How to Build and Flash
This project is configured for **PlatformIO**. To build and flash the code to the board:

1. Clone this repository to your local machine.
2. Open the project folder in VS Code (ensure the PlatformIO extension is installed).
3. Connect the STM32F0DISCOVERY board via the Mini-USB ST-LINK port.
4. Open the terminal and run the following command to compile and upload:
   ```bash
   pio run --target upload
