# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

RoboMaster Infantry robot **Chassis board** firmware. STM32F407IGHx (DJI C-Board), FreeRTOS, 4-wheel Mecanum drive. The sibling **Gimbal board** lives at `../../Gimbal/HAL_Template-main/`. Both boards communicate over CAN bus.

## Build System

- **IDE:** Keil MDK-ARM V5 (V5.38a). No Makefile/CMake exists.
- **Project file:** `MDK-ARM/HAL_Template.uvprojx`
- **Compiler:** ARM Compiler V5.06u7 (ARMCC)
- **Output:** `MDK-ARM/HAL_Template/HAL_Template.hex`
- **DSP library:** Uses `arm_cortexM4lf_math.lib` (with FPU), not `arm_cortexM4l_math.lib`
- **CubeMX project:** `HAL_Template.ioc` — peripheral configs are auto-generated into `Core/`

There is no command-line build. Builds are done via Keil GUI or the Keil Assistant VSCode extension.

## Architecture (5-Layer, Top-Down)

```
Application/Tasks   — FreeRTOS tasks (control loops, communication)
Application/API     — Pure algorithm APIs (quaternion EKF, trajectory solving). No global state here.
Components/         — Reusable modules: Device drivers, Algorithm libs, Controllers (PID, SMC)
Bsp/                — Board Support Package. ONLY layer that may call STM32 HAL functions directly.
Core/               — CubeMX-generated init code (main.c, peripheral configs, FreeRTOS setup)
```

**Rules:** No cross-layer calls (only call downward). No HAL calls outside `Bsp/`. `Application/API` must not define global variables.

## FreeRTOS Tasks (all 1 kHz)

| Task | Priority | Role |
|------|----------|------|
| `INS_Task` | Realtime | BMI088 IMU read (SPI), quaternion EKF fusion → Euler angles |
| `Comm_Task` | Realtime | CAN TX motor commands, CAN RX gimbal feedback, mode management |
| `Chassis_Task` | AboveNormal | Mecanum inverse kinematics, 4x wheel PID, power limiting |
| `Shoot_Task` | AboveNormal | Friction wheels + ammo feeder PID, heat management FSM |

Tasks share state via global structs: `Comm_Info`, `INS_Info`, `Chassis_Info`, `Shoot_Info`.

## CAN Bus Protocol

**CAN1 (chassis motors):**
- TX `0x200`: 4x wheel motor currents (M3508, IDs 0x201-0x204)
- TX `0x1FF`: shoot motor current (M2006, ID 0x205)
- RX `0x201-0x205`: motor feedback (encoder, velocity, current, temp)
- RX `0x300`: super capacitor voltage

**CAN2 (gimbal cross-link):**
- TX `0x02`: DM gimbal motor command (MIT mode: pos, vel, torque, Kp, Kd)
- RX `0x09`: DM motor feedback (angle, velocity, torque)
- RX `0x310`: referee bullet speed data

Chassis reads `Gimbal_Motor.Data.Angle` from CAN2 for gimbal-follow mode.

## UART Peripherals

| Port | Baud | Device | Notes |
|------|------|--------|-------|
| USART1 | 115200 | Referee system | DMA dual-buffer RX, IDLE interrupt |
| USART3 | 100000 | RC receiver | SBUS protocol |
| USB CDC | — | MiniPC (vision) | 500 Hz TX in Vision_Task |

## Mecanum Kinematics (Chassis_Task)

Wheel mapping: FL=0, BL=1, BR=2, FR=3.
```
wheel[FL] = -Vx - Vy - Vw
wheel[BL] =  Vx - Vy - Vw
wheel[BR] =  Vx + Vy - Vw
wheel[FR] = -Vx + Vy - Vw
```
Body-frame velocities are rotated by gimbal yaw offset before kinematics.

## Key Config Location

`Application/Tasks/Inc/config.h` — IMU axis remapping, armor dimensions, ballistic coefficients, physics constants. Axis indices must match the C-Board mounting orientation.

## Motor Types

- **M3508** (chassis wheels): 1:19 reduction, 8192-count encoder, CAN control
- **M2006** (ammo feeder): 1:36 reduction
- **DM motor** (gimbal): direct drive, MIT protocol over CAN2

## Power Limiting

`PowerCtrl.c` implements RLS-estimated motor power model. Solves quadratic `A*I^2 + B*I + C = 0` to attenuate currents within referee power budget.

## Style Guide

Follow [Google C++ Style Guide](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/) (adapted for C). The codebase uses PascalCase for type names/structs and snake_case/camelCase mixed for functions.

## Common Pitfalls

- CubeMX regeneration overwrites `Core/` files — protect user code inside `/* USER CODE BEGIN/END */` blocks
- Kalman filter init requires increasing heap beyond default `0x0200` in `startup_stm32f407xx.s` (set via CubeMX Linker Settings → Minimum Heap Size)
- DSP library must be the FPU variant (`arm_cortexM4lf_math.lib`)
