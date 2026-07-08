# Hardware Decisions

This document records important hardware decisions made during the development of Brawl Box Mini.

## Display

### Current Prototype
- 1.3" OLED Display
- Selected because it was available in the college inventory.

### Future Version
- 2.8" TFT SPI Display
- Planned for the Brawl Box Emulator project to support richer graphics and NES-style gameplay.

---

## Audio

### Current Status
Testing is underway between:

- PAM8403 Amplifier
- MAX98357A I2S Amplifier

The final amplifier will be selected after hardware testing with the available speakers.

---

## Controls

Currently evaluating:

- Analog Joystick
- Tactile Push Buttons

Joystick is currently used for rapid prototyping.
Final production version may switch to buttons depending on gameplay feel.

---

## Power System

Power Architecture:

LiPo Battery
→ TP4056 Type-C Charger
→ MT3608 Boost Converter
→ ESP32 Dev Board

This allows rechargeable battery operation while keeping the electronics modular.

---

## PCB

Current PCB Version:
- Single Layer
- Designed for college PCB fabrication process (UV exposure and chemical etching)

Future revision may include:
- Double layer routing
- Proper silkscreen
- Mounting holes
- Optimized placement