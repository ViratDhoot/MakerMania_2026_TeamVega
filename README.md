# Team Vega | MakerMania 2026

<p align="center">
  <img src="images/Brawl Box Mini PCB Routing.png" width="85%" height="" alt="Brawl Box Mini PCB">
</p>

<h1 align="center">🎮 Brawl Box</h1>

<p align="center">
A handheld multiplayer gaming platform built around ESP32 for <b>MakerMania 2026</b>.
</p>

<p align="center">

<img src="https://img.shields.io/badge/MakerMania-2026-2563EB?style=for-the-badge" />
<img src="https://img.shields.io/badge/Team-Vega-7C3AED?style=for-the-badge" />
<img src="https://img.shields.io/badge/Hardware-ESP32-10B981?style=for-the-badge" />
<img src="https://img.shields.io/badge/PCB-KiCad-E11D48?style=for-the-badge" />
<img src="https://img.shields.io/badge/Status-Active%20Development-F59E0B?style=for-the-badge" />

</p>

<p align="center">

<a href="docs/Project Specs - Brawl Box Mini/README.md">
<img src="https://img.shields.io/badge/📄_Project_Specifications-View-success?style=flat-square">
</a>

<a href="https://groovy-target-365.notion.site/Brawl-Box-384fc8af23368001a3b7db0b6b2d9bc3?pvs=73">
<img src="https://img.shields.io/badge/📦_Live_BOM-Notion-black?style=flat-square&logo=notion">
</a>

<a href="Training%20Material/README.md">
<img src="https://img.shields.io/badge/📚_Training_Material-View-blue?style=flat-square">
</a>

<a href="https://youtu.be/96Pshy8Dwqc">
<img src="https://img.shields.io/badge/🎬_BusyBuds_Ad-Watch-red?style=flat-square&logo=youtube">
</a>

<a href="https://youtu.be/p63lrrhlUBI">
<img src="https://img.shields.io/badge/😂_BusyBuds_Bloopers-Watch-red?style=flat-square&logo=youtube">
</a>

</p>

---

# Repository Overview

This repository documents **Team Vega's complete MakerMania 2026 journey** at **MBF Tinkerers' Lab, VESIT**.

It serves as a central workspace for documenting our engineering process—from problem discovery and user research to PCB design, embedded systems development, prototyping, testing, documentation, and final product development.

Our primary project is **Brawl Box**, a handheld multiplayer gaming platform built around ESP32.

Unlike traditional phone-based multiplayer games, Brawl Box focuses on **physical interaction**, **wireless multiplayer gameplay**, and **embedded hardware**, making it a fun and expandable electronics platform rather than just a single game.

---

# Current Project

## 🎮 Brawl Box Mini

The first version currently under development.

A compact OLED-based handheld built around the ESP32 with local multiplayer support using **ESP-NOW**.

Current hardware includes:

- ESP32-WROOM-32
- 1.3" OLED Display
- Joystick
- Rotary Encoder
- Speaker (Testing)
- Rechargeable LiPo Battery
- TP4056 Charging
- MT3608 Boost Converter

Current focus:

- PCB fabrication
- Firmware development
- Game development
- Hardware testing
- Prototype assembly

---

## 🕹 Future Roadmap

After completing **Brawl Box Mini**, the project will evolve into **Brawl Box Emulator**.

Planned upgrades include:

- 2.8" TFT Display
- MicroSD Card
- NES/GameBoy Emulator
- Larger Battery
- Better Audio
- Improved Enclosure
- Multiple Game Support

The Mini serves as the foundation for this future version.

---

# Quick Links

| Resource | Link |
|----------|------|
| 📄 Project Specifications | [`docs/Project Specs - Brawl Box Mini`](docs/Project%20Specs%20-%20Brawl%20Box%20Mini/README.md) |
| 📦 Live Component Tracker | https://groovy-target-365.notion.site/Brawl-Box-384fc8af23368001a3b7db0b6b2d9bc3?pvs=73 |
| 📊 User Research Summary | [`docs/User Research/Problem Statement Response Summary.md`](docs/User%20Research/Problem%20Statement%20Response%20Summary.md) |
| 📑 Google Form Responses | [`docs/User Research`](docs/User%20Research/) |
| 🎬 BusyBuds Documentation | [`Training Material/Week 1 Useless Product`](Training%20Material/Week%201%20Useless%20Product/) |
| 🧠 SCAMPER Activity | [`Week 2 - SCAMPER Activity`](Training%20Material/Week%202%20-%20SCAMPER%20Activity/) |
| 💡 Training Material | [`Training Material`](Training%20Material/) |

---

# Current Status

| Stage | Status |
|--------|:------:|
| Problem Discovery | ✅ |
| User Research | ✅ |
| Project Selection | ✅ |
| Component Planning | ✅ |
| PCB Schematic | ✅ |
| PCB Layout | 🟡 Optimizing |
| Prototype Assembly | 🟡 In Progress |
| Hardware Testing | ⏳ |
| Game Development | ⏳ |
| Multiplayer | ⏳ |
| Enclosure Design | ⏳ |
| Final Demonstration | ⏳ |

---

# Repository Structure

```text
.
│
├── cad/
│   ├── PCB/
│   ├── KiCad Projects/
│   ├── Symbols & Footprints/
│   └── PCB 3D Models/
│
├── code/
│
├── docs/
│   ├── Project Specs - Brawl Box Mini/
│   ├── User Research/
│   ├── Hardware Decisions/
│   ├── Testing/
│   ├── Known Issues/
│   └── Future Improvements/
│
├── images/
│
├── Training Material/
│
├── README.md
└── Instruction.md
```

---

# Progress Log

| Week | Activity | Status |
|------|----------|:------:|
| Week 1 | Startup Speed Dating | ✅ |
| Week 1 | Fusion 360 Training | ✅ |
| Week 1 | Laser Cutting | ✅ |
| Week 1 | 3D Printing | ✅ |
| Week 1 | BusyBuds Useless Product | ✅ |
| Week 1 | GitHub Documentation Setup | ✅ |
| Week 2 | Problem Discovery | ✅ |
| Week 2 | User Research Analysis | ✅ |
| Week 2 | SCAMPER Activity | ✅ |
| Week 2 | ESP32 Revision | ✅ |
| Week 3 | Brawl Box Ideation | ✅ |
| Week 3 | Component Planning | ✅ |
| Week 4 | PCB Schematic | ✅ |
| Week 4 | PCB Routing | 🟡 |
| Week 5 | Prototype Assembly | 🟡 |
| Week 6 | Firmware Development | ⏳ |

---
# 1. Team Identity

---

## Team Name

# **Team Vega** ⭐

<p align="center">
  <img src="images/Team_Image.jpeg" width="80%" alt="Team Vega">
</p>

---

## Team Members

| Member | Branch | Year | Primary Responsibilities | Current Focus |
|---------|--------|------|--------------------------|---------------|
| **Aarya Tanwade** | ECS | FE |Embedded systems, PCB design, firmware, documentation, video editing | Brawl Box Mini PCB development, GitHub documentation, single-player game development, 3D Model/Enclosure |
| **Saket Kunjathur** | CMPN | FE | Game ideation, Software, Game logic, Prototyping |Multiplayer Game Development |
| **Virat Dhoot** | AURO | SE | Ideation, testing, project discussions | Currently occupied with KT examinations |

---

## Team Vision

Our objective is to build practical, well-engineered hardware products by combining electronics, embedded systems, CAD, rapid prototyping, and product design.

Rather than simply completing activities, this repository documents our engineering process—from identifying problems to designing, prototyping, testing, and continuously improving our solutions.

---

# Training Journey

MakerMania started with several hands-on activities to build familiarity with rapid prototyping, fabrication tools, electronics, documentation, and product thinking before beginning the final innovation project.

---

# Week 1 — Foundations

## Activities Completed

- ✅ Startup Speed Dating
- ✅ Fusion 360 Basics
- ✅ Laser Cutting
- ✅ 3D Printing
- ✅ Useless Product Activity
- ✅ Product Advertisement
- ✅ GitHub Documentation

During the first week, the focus was on becoming familiar with the complete product development workflow.

We learned how to:

- Design basic CAD models using Fusion 360
- Prepare laser-cuttable DXF files
- Understand the complete 3D printing workflow
- Present ideas through storytelling
- Maintain engineering documentation using GitHub

Most importantly, we learned that **good engineering is not only about building products, but also about communicating ideas effectively.**

Detailed documentation of every activity is available here:

📂 **Training Material**

```
Training Material/
```

---

# Week 1 Highlight — BusyBuds

One of the most memorable activities was creating a completely useless product.

Our team built **BusyBuds**.

Instead of solving a real problem, BusyBuds solves a fictional one:

> "Looking busy without actually listening to anyone."

BusyBuds are solid fake earbuds.

They have:

- ❌ No Bluetooth
- ❌ No Battery
- ❌ No Audio
- ❌ No Charging

They simply help you *look* busy.

Despite being intentionally useless, the challenge was to convince people that they actually needed the product.

This activity taught us:

- Product positioning
- Marketing
- Storytelling
- Product presentation
- Creative thinking
- Video production

---

## BusyBuds Gallery

<p align="center">

<img src="Training%20Material/Week%201%20Useless%20Product/BusyBuds%203D%20Printed.jpeg" width="42%">
&nbsp;&nbsp;
<img src="Training%20Material/Week%201%20Useless%20Product/BusyBuds%20Thumbnail.jpeg" width="42%">

</p>

---

### Related Resources

| Resource | Link |
|----------|------|
| Documentation | `Training Material/Week 1 Useless Product/README.md` |
| Product Advertisement | https://youtu.be/96Pshy8Dwqc |
| Bloopers / Behind the Scenes | https://youtu.be/p63lrrhlUBI |
| STL Files | `Training Material/Week 1 Useless Product/` |

---

# Week 2 — From Ideas to Engineering

Week 2 marked the transition from training activities to actual product development.

Instead of learning individual tools, the focus shifted towards identifying meaningful problems and evaluating them from an engineering perspective.

---

## Activities Completed

- ✅ Problem Discovery
- ✅ User Research
- ✅ Google Form Analysis
- ✅ SCAMPER Activity
- ✅ ESP32 Revision
- ✅ Hardware Ideation
- ✅ Component Planning
- ✅ PCB Design

---

## Problem Discovery

We collected and reviewed real-world problem statements through:

- Google Forms
- Team discussions
- Daily observations
- Mentor feedback

Rather than selecting the first interesting idea, multiple concepts were evaluated based on:

- User pain
- Hardware feasibility
- Cost
- Prototype complexity
- Available timeline

This process helped us eliminate several ideas before arriving at our current project direction.

---

## SCAMPER Activity

As part of the ideation process, our team explored different solution spaces using the SCAMPER framework.

Some ideas discussed included:

- Local train bag support
- Delivery worker safety
- Automatic car AC controller
- Gym equipment tracker
- Student productivity devices

Although these ideas were not selected, the activity helped us practice structured product thinking and evaluate ideas critically instead of emotionally.

The complete activity presentation is available inside:

```
Training Material/
└── Week 2 - SCAMPER Activity/
```

---

## ESP32 Revision

Before beginning the final project, we revised the ESP32 development workflow through a simple hardware exercise involving GPIO programming and LED control.

This session helped refresh:

- ESP32 programming
- GPIO handling
- Arduino workflow
- Hardware debugging

The revision activity can be found in:

```
Training Material/
└── Week 2 - ESP32 Revision/
```

---

## Choosing Our Final Direction

After multiple rounds of discussion, we shortlisted **Brawl Box** as our primary project.

Unlike our earlier concepts, Brawl Box offered:

- Strong hardware scope
- Embedded systems integration
- PCB design
- Wireless communication
- Game development
- Product design
- Future expandability

The project also allowed us to build something genuinely enjoyable while still demonstrating substantial engineering depth.

It has since become the primary focus of Team Vega's MakerMania journey.

---

# 5. Solution Ideation

## Brainstormed Ideas

| Idea                                              | Source                              | Advantages                                                                                                | Challenges                                                                      | Current Status                |
| ------------------------------------------------- | ----------------------------------- | --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------- | ----------------------------- |
| Non-invasive automatic AC control for manual cars | Form response / user input          | Clear user pain, hardware-based, does not require modifying car electronics                               | Reliable mounting, vibration, actuator force, dashboard compatibility           | Discussed                     |
| Gym equipment movement quality tracker            | Team discussion                     | Practical, sensor-based, useful for beginners, measurable movement data                                   | Cannot track full body posture with only equipment sensor, needs careful scope  | Discussed                     |
| Gig worker heat and safety tracking device        | SCAMPER activity / team discussion  | Socially relevant, low-cost wearable/device direction, useful in Indian outdoor conditions                | Needs focused problem framing, sensor accuracy, comfort, battery life           | Used for SCAMPER activity     |
| AI road-safety detection system                   | Team discussion / mentor feedback   | High-impact idea, connects to traffic safety and violations                                               | Costly, AI-heavy, power-heavy, difficult for 30-day prototype                   | Deprioritized                 |
| Bus tracking / public transport issue             | Form response                       | Useful for commuters, clear user inconvenience                                                            | May become software/infrastructure-heavy, needs external data or system support | Discussed                     |
| Wake-up / alarm problem                           | Form response                       | Common issue, possible physical product direction                                                         | Needs stronger uniqueness and validation                                        | Discussed                     |
| Brawl Box Mini handheld multiplayer console       | Team discussion / mentor discussion | Hardware-first, buildable, interactive, expandable, allows display/buttons/audio/vibration/enclosure work | Needs strong gameplay, clean enclosure, and stable wireless communication       | **Selected direction**        |

---

## Selected Concept

The current selected project direction is **Brawl Box Mini** — a compact handheld multiplayer gaming console prototype.

The core game is **Maze Blaze**, a 2-player local multiplayer game where players spawn from different corners of a dynamically generated maze and race toward the center while collecting abilities such as speed boosts and bomb-based attacks. Each player uses a separate handheld device featuring a 1.3" OLED display, physical buttons, rotary encoder, PAM8403 sound feedback, vibration feedback, and ESP-NOW wireless communication.

While *Maze Blaze* is the flagship multiplayer experience, the Brawl Box Mini is designed as a platform that also supports single-player fallback games via a unified menu.

Detailed project specifications and component list:
[View Brawl Box Mini Project Specs](docs/Project%20Specs%20-%20Brawl%20Box%20Mini/README.md)

Live component tracker:
[View Brawl Box Notion BOM](https://groovy-target-365.notion.site/Brawl-Box-384fc8af23368001a3b7db0b6b2d9bc3?pvs=73)

---
# 6. System Design (V1)

## High-Level Description

**Brawl Box Mini (V1)** is a 2-device handheld multiplayer gaming system. Each device acts as an individual player console with its own OLED screen, tactile controls, audio output, haptic feedback, and portable battery power.

The primary interaction revolves around physical controls: the D-Pad is used for movement, while the Rotary Encoder adds a hardware-first interaction layer for menu scrolling and tactical bomb targeting.

---

## Block Diagram

```text
🔋 3.7V LiPo Battery
   ↳ TP4056 Type-C Charging Module
     ↳ Slide Switch
       ↳ MT3608 Boost Converter (set to 5V)
         ↳ ESP32 DevKit V1 (WROOM-32)
            ├── 1.3" I2C OLED Display
            ├── Tactile Push Buttons
            ├── Rotary Encoder
            ├── PAM8403 Audio Amplifier + Speaker
            ├── DC Vibration Motor
            └── ESP-NOW Wireless Sync
```

---

## Inputs

| Input                            | Purpose                                                        |
| -------------------------------- | -------------------------------------------------------------- |
| Push buttons                     | D-Pad movement, action, select, back/menu controls             |
| Rotary encoder                   | Menu navigation, player selection, and bomb targeting          |
| Power switch                     | Turns the device ON/OFF                                        |
| Wireless data from other devices | Receives opponent position, game state, and multiplayer events |

---

## Outputs

| Output                         | Purpose                                                             |
| ------------------------------ | ------------------------------------------------------------------- |
| 1.3" OLED display              | Shows game screen, maze, player status, menu, health, and abilities |
| 8Ω Speaker                     | Plays game sound effects via the ESP32 DAC and PAM8403 amplifier    |
| Vibration motor                | Gives haptic feedback for bomb hits, damage, and alerts             |
| Wireless data to other devices | Sends player movement, ability use, and game events                 |

---

# 7. Technical Planning

## Electronics (V1 Core)

| Component                                           | Purpose                                                                                                     |
| --------------------------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| ESP32 DevKit V1 (WROOM-32)                          | Main microcontroller for game logic, graphics, inputs, audio control, vibration, and wireless communication |
| 1.3" I2C OLED Display                               | Main visual interface for gameplay and menus                                                                |
| Tactile Push Buttons                                | Movement and action controls                                                                                |
| Rotary Encoder                                      | Menu control, opponent targeting, and bomb placement                                                        |
| PAM8403 Audio Amplifier                             | Drives audio output from the ESP32 internal DAC                                                             |
| 8Ω Speaker                                          | Audio output for game effects                                                                               |
| DC Vibration Motor Module                           | Haptic feedback during gameplay                                                                             |
| 3.7V 2000mAh LiPo Battery                           | Portable power source                                                                                       |
| TP4056 Type-C Charging Module                       | Charges the LiPo battery                                                                                    |
| MT3608 Boost Converter                              | Boosts battery voltage to 5V for the ESP32 dev board                                                        |
| Zero PCB, jumper wires, hookup wire, JST connectors | Prototype assembly and internal wiring                                                                      |

---

## Software

| Tool / Library                      | Purpose                                    |
| ----------------------------------- | ------------------------------------------ |
| Arduino IDE / PlatformIO            | ESP32 C++ programming                      |
| Adafruit_SSD1306 / U8g2             | OLED display graphics and UI rendering     |
| ESP-NOW                             | Wireless communication between devices     |
| ESP32 Internal DAC (`driver/dac.h`) | Audio signal generation for PAM8403        |
| Rotary Encoder Library              | Reading rotary encoder movement            |
| GPIO input handling                 | Button controls and debouncing             |
| GitHub Markdown                     | Project documentation                      |
| Notion                              | Live component tracker and BOM management  |

---

## Mechanical / CAD

Mechanical design will focus on building a compact, clean handheld console-style enclosure.

Current considerations:
* 3D printed handheld body.
* Screen cutout and recessed display area.
* D-pad style 3D printed button caps.
* Rotary encoder knob placement for thumb ergonomics.
* Speaker holes and charging port cutouts.
* Internal mounting points for the single-layer custom PCB and battery.

---

## Current Development Status

| Task                                 | Status         |
| ------------------------------------ | -------------- |
| Game concept selected                | ✅ Completed    |
| Component list prepared              | ✅ Completed    |
| Live Notion BOM created              | ✅ Completed    |
| V1 Hardware architecture & schematic | ✅ Completed    |
| Game logic implementation            | 🔄 In progress |
| ESP-NOW Host/Client lobby code       | 🔄 In progress |
| V1 PCB Routing (Single-layer)        | 🔄 In progress |
| Audio (DAC + PAM8403) testing        | ⏳ Pending      |
| Enclosure design                     | ⏳ Pending      |
| Final prototype assembly             | ⏳ Pending      |

---
# 8. Prototype Development

## Version 1 (Breadboard & Core Logic)
The first prototype phase focuses on getting a single handheld setup working on a breadboard with the ESP32 (WROOM), 1.3" OLED display, tactile buttons, rotary encoder, PAM8403 audio, vibration motor, and power system.
* **Planned tests:** OLED initialization, input reading, UI menu rendering, audio output via internal DAC, and power stability.

## Version 2 (Multiplayer Sync & PCB)
The second prototype phase focuses on the custom single-layer PCB integration and the **Maze Blaze** game logic.
* **Planned tests:** ESP-NOW communication, player movement syncing, dynamic maze rendering, and rotary-targeted bomb logic between two separate ESP32 units.

## Final Prototype
The final prototype will include 2 fully assembled handheld devices with playable multiplayer gameplay, sound, vibration, and clean 3D-printed enclosures.

---

# 9. Testing & Validation

## Testing Plan

| Test                   | Success Criteria                                                      |
| ---------------------- | --------------------------------------------------------------------- |
| Basic electronics test | ESP32, display, buttons, audio, vibration, and power work correctly   |
| Display test           | 1.3" OLED display shows menu and game screen clearly without lag      |
| Input test             | Tactile buttons and rotary encoder respond reliably and are debounced |
| Audio test             | PAM8403 outputs clear game effects from the ESP32 DAC                 |
| Vibration test         | Vibration motor triggers on specific game events (e.g., getting hit)  |
| Power test             | Device runs from LiPo battery through TP4056 and MT3608 boost module  |
| ESP-NOW test           | Both devices communicate wirelessly without a router/internet         |
| Gameplay test          | Players can move, collect abilities, attack, and reach the center     |
| Mechanical fit test    | PCB and electronics fit securely inside the 3D printed enclosure      |
| Final demo test        | Prototype demonstrates *Maze Blaze* multiplayer loop successfully     |

---

## User Feedback

| User        | Feedback    | Action Taken |
| ----------- | ----------- | ------------ |
| In progress | In progress | In progress  |

---

# 10. Innovation Assessment

## Existing Solutions
Existing solutions and reference categories being considered:
* Phone-based multiplayer games
* Board games
* Electronic handheld toys
* DIY ESP32 game consoles
* Mini retro gaming devices
* Classroom/game-based activity devices

---

## What Makes This Different?
Brawl Box Mini is different from a normal phone game or simple board game because it combines:
* A separate physical handheld device for each local player.
* Physical, tactile controls utilizing a Rotary Encoder for in-game mechanics.
* Robust local multiplayer sync (ESP-NOW) that bypasses traditional Wi-Fi routers.
* Haptic physical feedback (vibration) and audio mapped to game events.
* A fully student-designed single-layer PCB architecture.

---

## Innovation Score

| Parameter       | Score / Note                                                                                |
| --------------- | ------------------------------------------------------------------------------------------- |
| Novelty         | Medium to High — depends on gameplay polish and physical interaction                        |
| Technical Depth | High for the team level — ESP32, display, audio, power, vibration, communication, enclosure |
| Feasibility     | Medium to High — buildable but requires careful integration on a single-layer board         |
| Impact          | Medium — entertainment/education/activity product                                           |
| Scalability     | Medium — same hardware can support more simple games later via firmware updates             |

---

# 11. Business & Deployment

## Target Users
* Students and children
* Casual players
* Schools / activity spaces
* Maker events and technical showcases
* Game-based learning workshops

---

## Estimated Cost

Current estimated component cost for **2 devices (V1 Prototype)**:

| Section                         | Approx. Cost |
| ------------------------------- | -----------: |
| Components used for 2 devices   |       ₹2,510 |
| Shared / Bench components       |         ₹395 |
| **Estimated Total** |    **₹2,905** |

Detailed live component tracker:
[View Brawl Box Notion BOM](https://groovy-target-365.notion.site/Brawl-Box-384fc8af23368001a3b7db0b6b2d9bc3?pvs=73)

---

## Market Opportunity
Brawl Box Mini can potentially be positioned as:
* A student-built gaming console prototype.
* A physical multiplayer activity device.
* A maker-event demonstration product.
* An open-source hardware kit for learning embedded systems and game design.
* A screen-free multiplayer play experience.

---

## Sustainability Considerations
Current considerations:
* Rechargeable battery-powered design.
* Reusable enclosure and repairable modular internal components.
* Firmware-based game expansion instead of building new hardware for every game.
* Minimal material waste through iterative CAD and enclosure design.

---

# 12. Final Demonstration

## Prototype Images
*Pending prototype development.*

---

## Demonstration Video Link
*Pending prototype demonstration.*

---

## GitHub Repository
Current repository: Team Vega MakerMania 2026 repository.

---

## Presentation Link
*Pending final presentation.*

---

# 13. Reflection

## What Worked Well?

**Week 1:**
* Team completed the useless product activity.
* BusyBuds was taken from an idea to a 3D printed product and advertisement.
* We got hands-on exposure to CAD, laser cutting, 3D printing, documentation, and video-based pitching.

**Week 2:**
* Problem discovery started with Google Form responses and informal discussions.
* Evaluated ideas based on user pain, feasibility, cost, and hardware scope using SCAMPER.
* The team locked in a buildable hardware-first project direction (Brawl Box Mini).

**Week 3:**
* ESP-NOW multiplayer lobby and Host/Client room code logic successfully built.
* Maze generation and single-player menu structure are actively in progress.
* Single-layer bottom-routed PCB layout drafted in KiCad.

---

## What Failed / Challenges?

**Week 1:**
* The first 3D print attempt for BusyBuds needed improvement because the support setup was not planned well.
* Documentation could have been updated more frequently during the activity.

**Week 2:**
* Early ideas were too vague or difficult to frame clearly (e.g., local-train bag holder shifted the load instead of reducing it).
* High-impact ideas were too expensive, AI-heavy, or difficult to prototype within the current sprint.

**Week 3:**
* **Audio Interferences:** Realized that combining the ESP32's internal DAC with Wi-Fi (ESP-NOW) might cause static noise on the PAM8403 due to CPU interrupts. Breadboard testing is currently prioritized to debug this.
* **PCB Optimization:** Initial random placement of tactile buttons on the PCB requires a complete rework to ensure proper thumb ergonomics before final track routing.

---

## Key Learnings

* CAD and 3D printing require strict attention to dimensions, supports, orientation, and printability.
* A product pitch depends not only on the object, but also on framing, storytelling, and presentation.
* Hardware ideas need to be checked for cost, feasibility, mounting, durability, and user value.
* Power architecture, communication, display protocols, and physical controls must be planned together as a unified system, not isolated modules.
* Preserving our V2 double-layer TFT Emulator architecture separately allowed us to establish a clear future roadmap while keeping the current sprint focused and achievable.

---

## Next Steps

* Finalize V1 PCB button placement for proper thumb ergonomics.
* Conduct strict breadboard testing for the PAM8403 audio amplifier alongside ESP-NOW transmission.
* Etch and solder the V1 single-layer PCBs.
* Finalize single-player fallback games and *Maze Blaze* sync logic.
* Design and fabricate the 3D enclosure in Fusion 360.
* Document every major test, issue, and fix continuously on GitHub.

---

# 14. Final Deliverables Checklist

* [x] Week 1 Training Completed
* [x] Useless Product Activity Completed
* [x] Google Form Responses Reviewed
* [x] SCAMPER Activity Completed
* [x] ESP32 Revision Activity Completed
* [x] Project Direction Selected
* [x] Component List Prepared
* [x] Notion BOM Created
* [x] Project Specs README Added
* [x] V1 System Design & Schematic Complete
* [ ] V1 PCB Routing Complete
* [ ] ESP-NOW Multiplayer Logic Sync Complete
* [ ] Prototype Assembled & Demonstrated
* [ ] Testing Completed
* [ ] Final Pitch Presentation Submitted

---

# MAKERMANIA FINAL PITCH

Each team will present:

1. Problem
2. User Research
3. Insights
4. Solution
5. Prototype Demo
6. Innovation & Patentability
7. Future Roadmap

**Presentation Time:** 5 Minutes  
**Q&A:** 3 Minutes