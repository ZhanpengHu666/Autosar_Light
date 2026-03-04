 # Autosar Light (S32K144)

  AUTOSAR turn signal project based on NXP S32K144 and Vector MICROSAR.
  This repository contains the full flow of signal decision, arbitration, and actuator control.

  ## Features

  - Left and right turn signal control (long flash and short flash)
  - Hazard light control
  - Emergency brake related input handling
  - 10 ms periodic execution through AUTOSAR RTE

  ## Software Architecture

  1. `TurnLight`
  - Parses input signals and decides turn signal strategy.
  - Main file: `Appl/Source/TurnLight.c`

  2. `TurnLightArb`
  - Arbitrates requests by priority and outputs FL/FR/RL/RR commands.
  - Main file: `Appl/Source/TurnLightArb.c`

  3. `TurnLightAct`
  - Converts arbitration results to actuator commands and calls IoHwAb APIs.
  - Main file: `Appl/Source/TurnLightAct.c`

  4. `RTE/OS Scheduling`
  - `TurnLight_Runnable_10ms`, `TurnLightArb_Runnable_10ms`, and `TurnLightAct_Runnable_10ms`
    are scheduled in `OsTask_BSW_SCHM`.
  - Main file: `Appl/GenData/Rte.c`

  ## Directory Overview

  - `Appl/`: application source and generated data (`Source` + `GenData`)
  - `BSW/`: AUTOSAR basic software modules
  - `Config/`: system and developer configuration (ARXML, DCM, etc.)
  - `MCAL/`: MCAL modules and configuration resources
  - `S32K144_Start.dpa`: DaVinci project file
  - `ASR_S32K144_Start.ewp`: IAR project file

  ## Recommended Environment

  - MCU: S32K144
  - IDE: IAR Embedded Workbench (`ASR_S32K144_Start.ewp`)
  - Config tool: Vector DaVinci (`S32K144_Start.dpa`)
  - AUTOSAR stack: MICROSAR (BSW + MCAL)

  ## Quick Start

  1. Clone repository

  ```bash
  git clone https://github.com/ZhanpengHu666/Autosar_Light.git
  cd Autosar_Light

  2. Open ASR_S32K144_Start.ewp in IAR.
  3. Select build configuration (for example, Debug).
  4. Build and download to target board.

  ## Key Input Signals (Examples)

  - TurnLampSw
  - TurnLampFb_FL/FR/RL/RR
  - EmergencyBrakeLight

  See signal mapping in:

  - Config/System/SystemExtract.arxml

  ## Repository Notes

  - Build artifacts and logs are ignored (for example Debug/, Log/, Appl/lst/).
  - Third-party AUTOSAR/MCAL content may be license-restricted. Follow vendor license terms.
