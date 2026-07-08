# Brawl Box Mini (V1)

A compact ESP32-powered handheld multiplayer gaming console being developed by **Team Vega** for **MakerMania 2026**.

Brawl Box Mini combines embedded systems, PCB design, wireless communication, game development, and product design into a portable gaming device capable of running simple multiplayer experiences.

---

# Overview

Brawl Box Mini is the first prototype in the Brawl Box series.

The objective of this version is to build a complete handheld gaming device from scratch while learning the complete product development cycle including:

- Embedded systems
- PCB Design
- Firmware Development
- Wireless Communication
- Hardware Testing
- Product Design
- Rapid Prototyping
- Enclosure Design

Unlike a traditional electronics project, the goal is to create an actual handheld gaming product rather than just a circuit.

---

# Project Vision

Instead of building a single game, Brawl Box is intended to become a small handheld gaming platform capable of supporting multiple games.

The current focus is completing the first working hardware prototype (Mini V1). Once stable, the platform can be expanded with additional games, improved hardware, and eventually a TFT-based emulator version.

---

# Current Game Concept

The first multiplayer game planned for Brawl Box Mini is a maze-based battle game.

### Gameplay

- 3 handheld devices
- Wireless multiplayer communication using ESP-NOW
- Players spawn from different maze locations
- Reach the objective before opponents
- Collect power-ups
- Attack other players using special abilities
- Sound and vibration feedback during gameplay

The exact gameplay mechanics are still evolving alongside hardware development.

---

# Hardware Features

| Feature | Description |
|----------|-------------|
| Handheld Console | Compact portable gaming device |
| ESP32 Controller | Main processing unit |
| OLED Display | Displays menus and game graphics |
| Wireless Multiplayer | ESP-NOW communication |
| Analog Input | Joystick-based movement |
| Rotary Encoder | Navigation and selection |
| Rechargeable Battery | Portable LiPo-powered device |
| Audio Feedback | Speaker-based sound effects |
| Haptic Feedback | Vibration motor support |
| Custom PCB | Single-layer PCB designed in KiCad |

---

# Current Hardware Configuration

The current prototype consists of:

- ESP32-WROOM-32 Development Board
- 1.3" OLED Display (I²C)
- Analog Joystick
- Rotary Encoder
- Rechargeable LiPo Battery
- TP4056 Charging Module
- MT3608 Boost Converter
- Slide Power Switch
- PAM8403 Audio Amplifier *(currently under testing)*
- Compact 8Ω Speaker *(ordered, testing pending)*

Several hardware decisions are still being validated through testing before final assembly.

---

# Hardware Under Evaluation

The following components are currently being tested before finalizing the design.

| Component | Status |
|----------|--------|
| Joystick vs Direction Buttons | Under Evaluation |
| PAM8403 Amplifier | Testing Pending |
| MAX98357A I2S Amplifier | Backup Option |
| Speaker Performance | Testing Pending |
| PCB Component Placement | Being Optimized |

---

# System Architecture

```text
                LiPo Battery
                     │
                     ▼
        TP4056 Charging Module
                     │
                     ▼
             Power Switch
                     │
                     ▼
         MT3608 Boost Converter
               (3.7V → 5V)
                     │
                     ▼
         ESP32 Development Board
                     │
     ┌───────────────┼────────────────┐
     │               │                │
     ▼               ▼                ▼
 OLED Display     Joystick      Rotary Encoder
     │
     ▼
 Game Interface

ESP32
 ├── Audio Amplifier
 ├── Speaker
 ├── Vibration Motor
 └── ESP-NOW Multiplayer
```

---

# Power Architecture

Brawl Box Mini is powered using a single-cell 3.7V rechargeable LiPo battery.

Power flow:

```text
3.7V LiPo Battery
        │
        ▼
TP4056 Charging Module
        │
        ▼
Slide Switch
        │
        ▼
MT3608 Boost Converter
 (Boost to 5V)
        │
        ▼
ESP32 Dev Board (VIN/5V)
        │
        ▼
Onboard 3.3V Regulator
        │
        ▼
ESP32 + Peripherals
```

The ESP32 development board internally regulates 5V down to 3.3V for the microcontroller and onboard peripherals.

---

