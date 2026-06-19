# Brawl Box — Project Specifications

## Overview

**Brawl Box** is a handheld multiplayer gaming console prototype being developed by Team Vega for MakerMania 2026.

The first game planned for the device is a multiplayer maze-battle game where players spawn from different edges of the maze and race toward the center. Along the way, players can collect abilities such as speed boost, health, and bomb-based attacks.

The goal is to build a compact physical gaming device that combines embedded systems, game logic, wireless communication, sound, haptic feedback, and product-style enclosure design.

---

## Product Direction

Brawl Box is not just a single game. It is being designed as a small handheld console platform that can support multiple simple multiplayer games in the future.

### Current Game Concept

* 3-player handheld multiplayer game
* Each player gets one handheld device
* Players spawn from different edges/corners of the maze
* Objective: reach the center or complete the game objective first
* Players can collect abilities from the maze
* Bomb ability can be used to attack or freeze opponents
* Rotary encoder is used for selection/targeting
* Sound and vibration provide physical feedback

---

## Key Features

| Feature                      | Description                                               |
| ---------------------------- | --------------------------------------------------------- |
| Handheld console form factor | Each player has their own compact device                  |
| TFT display                  | Shows maze, player position, health, abilities, and menu  |
| Physical controls            | Push buttons and rotary encoder for gameplay              |
| Multiplayer communication    | ESP32-based wireless communication between devices        |
| Sound feedback               | DFPlayer Mini and speaker for game sound effects          |
| Haptic feedback              | Vibration motor for bomb hits, freeze effects, and alerts |
| Battery powered              | Portable device powered by a rechargeable LiPo battery    |
| Expandable game platform     | Future games can be added through firmware updates        |

---

## System Architecture

```text
LiPo Battery
↓
TP4056 Charging Module
↓
Power Switch
↓
MT3608 Boost Converter set to 5V
↓
ESP32-S3 Dev Board
├── TFT Display
├── Push Buttons
├── Rotary Encoder
├── DFPlayer Mini + Speaker
├── Vibration Motor
└── Wireless Communication with Other Devices
```

---

## Power Architecture

Each device uses a single-cell **3.7V LiPo battery**. The TP4056 module handles battery charging through USB Type-C. The MT3608 boost converter steps the battery voltage up to 5V.

This 5V output is supplied to the ESP32 development board through its 5V/VIN input. The ESP32 board’s onboard regulator then converts this 5V into 3.3V for the ESP32 chip and logic-level operation.

```text
3.7V LiPo Battery
→ TP4056 Type-C Charging Module
→ Slide Switch
→ MT3608 Boost Converter set to 5V
→ ESP32-S3 Dev Board 5V/VIN
→ Onboard 3.3V Regulation
```

---

## Component List

Detailed live component tracker:
[Brawl Box Notion Component List](https://groovy-target-365.notion.site/Brawl-Box-384fc8af23368001a3b7db0b6b2d9bc3?pvs=73)

---

## Components Used for Each Device

These components are required for each handheld device. Since the current prototype target is **3 devices**, this section will be multiplied by 3.

|  # | Component                                                                            | Quantity per Device | Approx. Price per Unit | Purpose                                                             |
| -: | ------------------------------------------------------------------------------------ | ------------------: | ---------------------: | ------------------------------------------------------------------- |
|  1 | ESP32-S3 N16R8 Dual USB-C Wi-Fi + Bluetooth MCU Development Board                    |                   1 |                   ₹630 | Main controller / brain of the handheld device                      |
|  2 | 2.8 inch SPI Screen Module TFT Interface 240×320 without Touch                       |                   1 |                   ₹500 | Game display for maze, menu, player status, health, abilities, etc. |
|  3 | Tactile Push Button Switch 6×6×5 mm                                                  |        1 pack of 10 |                    ₹15 | Movement buttons and action buttons                                 |
|  4 | 360 Degree Rotary Encoder Module                                                     |                   1 |                    ₹50 | Menu navigation, player selection, bomb targeting, and settings     |
|  5 | DFPlayer Mini MP3 Player Module                                                      |                   1 |                   ₹100 | Plays MP3 sound effects using a microSD card                        |
|  6 | 0.5W 8Ω Speaker                                                                      |                   1 |                    ₹50 | Audio output for DFPlayer Mini                                      |
|  7 | DC Vibration Motor Module                                                            |                   1 |                    ₹50 | Haptic feedback for bomb hit, freeze, damage, warning, etc.         |
|  8 | KP Original Battery 3.7V 2000mAh 2-Wire LiPo Rechargeable Battery Model KP-523450    |                   1 |                   ₹370 | Portable battery power for each device                              |
|  9 | 3 Pin Slide Switch                                                                   |                   1 |                     ₹5 | ON/OFF power switch                                                 |
| 10 | TP4056 1A Charging Module for 3.7V Li-ion Battery Type-C USB with Current Protection |                   1 |                    ₹20 | Charges the 3.7V LiPo battery safely                                |
| 11 | MT3608 DC-DC Step-Up Boost Converter Module                                          |                   1 |                    ₹50 | Boosts 3.7V battery voltage to 5V for the ESP32 dev board           |

**Approx. cost per device:** ₹1840
**Approx. cost for 3 devices:** ₹5520

---

## Shared Components

These components are shared/common components and do not need to be multiplied per device.

|  # | Component                                                         | Quantity | Approx. Price per Unit | Approx. Total | Purpose                                                                       |
| -: | ----------------------------------------------------------------- | -------: | ---------------------: | ------------: | ----------------------------------------------------------------------------- |
|  1 | 100nF 50V Disc Capacitor                                          |       10 |                     ₹1 |           ₹10 | Noise filtering and signal/power stability support                            |
|  2 | Zero PCB 4×6 inch General Purpose Dot PCB for DIY Electronics     |        1 |                    ₹30 |           ₹30 | General soldering and circuit prototyping                                     |
|  3 | 1×40 Female Berg Strip Connector                                  |        1 |                    ₹10 |           ₹10 | Header connector for mounting modules cleanly                                 |
|  4 | Jumper Wire Set — M2M, M2F, F2F, 40 pcs each                      |        1 |                   ₹160 |          ₹160 | Temporary prototyping and testing connections                                 |
|  5 | Hookup Wire — 2 meters × 5 colors, total 10 meters pack           |        1 |                   ₹100 |          ₹100 | Internal soldered wiring inside the devices                                   |
|  6 | 2 Pin JST Cable Connector Female Lock Type — 2.54mm Pitch, 10 pcs |        1 |                    ₹30 |           ₹30 | Battery and power connector wiring                                            |
|  7 | 2GB MicroSD Card                                                  |        1 |                   ₹130 |          ₹130 | Stores MP3 sound effects for DFPlayer Mini testing                            |
|  8 | Resistor Box — 150 Resistors and 30 Values                        |        1 |                    ₹40 |           ₹40 | Common resistor values for pullups, signal protection, debugging, etc.        |
|  9 | 100µF 50V Capacitor                                               |        5 |                     ₹3 |           ₹15 | Power smoothing; helps prevent ESP32 reset, display glitches, and audio noise |

**Shared components total:** ₹525

---

## Estimated Cost

| Section                   | Approx. Cost |
| ------------------------- | -----------: |
| Components for 3 devices  |        ₹5520 |
| Shared components         |         ₹525 |
| **Final Estimated Total** |    **₹6045** |

This estimate excludes 3D printing/enclosure material, screws/standoffs, shipping, and optional LED lighting.

---

## Planned Software Stack

| Area                      | Tool / Library                             |
| ------------------------- | ------------------------------------------ |
| Programming               | Arduino IDE / PlatformIO                   |
| Graphics                  | TFT_eSPI / Arduino graphics library        |
| Multiplayer communication | ESP-NOW                                    |
| Audio                     | DFPlayer Mini serial control               |
| Input handling            | GPIO buttons + rotary encoder              |
| Haptic feedback           | GPIO-controlled vibration motor module     |
| Documentation             | GitHub Markdown + Notion component tracker |

---

## Current Development Status

| Task                              | Status      |
| --------------------------------- | ----------- |
| Game concept finalized            | In progress |
| Component list prepared           | Completed   |
| Hardware architecture planned     | Completed   |
| Schematic/block diagram           | In progress |
| Game logic implementation         | Pending     |
| Multiplayer communication testing | Pending     |
| Enclosure design                  | Pending     |
| Final prototype assembly          | Pending     |

---

## Next Steps

1. Finalize component approval with mentor.
2. Order required components.
3. Build one working device first.
4. Test display, buttons, rotary encoder, sound, vibration, and power.
5. Implement basic single-player maze movement.
6. Add ESP-NOW communication between devices.
7. Build remaining devices.
8. Design and fabricate enclosure.
9. Test gameplay and refine interaction.
10. Document build progress continuously on GitHub.
