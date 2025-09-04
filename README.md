---

# Gat150Sol

> **Gat150Sol** — a prototype game created for the GAT150 course.
> Short tagline: *Fast-paced top-down shooter prototype with procedural spawn & simple upgrade system.*

---

## Table of contents

* [Project description](#project-description)
* [Core features](#core-features)
* [Extra features](#extra-features)
* [Screenshots](#screenshots-recommended)
* [Build & run instructions](#build--run-instructions)
* [Controls](#controls)
* [Known issues & limitations](#known-issues--limitations)
* [Credits & third-party libraries](#credits--third-party-libraries)



---

## Project description

**Gat150Sol** is a small prototype game built for the GAT150 course. The current build is intended as a desktop demo that showcases player movement, shooting mechanics, enemy spawning, simple AI, and a score HUD. The project is structured to be readable and extensible for course assignments and demos.

**Engine / language :** `<C++ with SDL3>`
**Purpose:** GAT150 course project & prototype for gameplay mechanics and assignment submission.

---

## Core features

* Player movement (top-down) with smooth controls.
* Player shooting with cooldown and projectile pooling.
* Enemy spawning system with increasing difficulty.
* HUD showing score.


---

## Extra features

* 4 Powerups (projectile changes, circle of bullets, to more bullets per shot).

---

## Screenshots 


* Base gameplay
<img width="1275" height="1025" alt="image" src="https://github.com/user-attachments/assets/a797494e-c1d5-4114-9d4e-67d82e6bbfd5" />

* Star powerup in effect
<img width="1275" height="1063" alt="image" src="https://github.com/user-attachments/assets/fa7bdd1a-5d75-4db1-b5e9-7dfa4883559b" />

* Triple powerup in effect
<img width="1281" height="1060" alt="image" src="https://github.com/user-attachments/assets/f06a6c49-a692-4107-895c-d71b111e87dc" />

* Laser powerup in effect
<img width="1274" height="1065" alt="image" src="https://github.com/user-attachments/assets/cdc48d3e-330e-41a3-a186-b51d70993015" />

* Heart power up in effect
<img width="1273" height="1057" alt="image" src="https://github.com/user-attachments/assets/58531520-e64c-4e6e-94eb-37ace92bb8db" />

---

## Build & run instructions

> Replace the matching section with the engine/language your repository uses. The general first step is cloning the repo:

```bash
git clone https://github.com/CodyAndGity/Gat150Sol.git
cd Gat150Sol
```
* Then navigate to Gat150Sol\Build
* Double click the exe


**Troubleshooting**

* If assets or packages are missing, open `Window → Package Manager` and install any missing packages.



### Windows specifics

If using Visual Studio, open `Gat150Sol.sln`,
build in Release, 
and run the produced `.exe`.

---

## Controls

(Replace with project-specific controls)

* Move:  `A` `D`
* Aim: Mouse movement
* Shoot: Left mouse button

---

## Known issues & limitations

* Physics can be unstable at very high frame rates — use fixed timestep if necessary.
* Sound mixing may clip when many SFX play at once.
* Pathfinding is simple — powerup may get stuck blocks on the map.
* Mobile input not implemented (desktop-only prototype).



---

## Credits & third-party libraries

**Engine & core libs**


* `SDL3` — [https://www.libsdl.org](https://www.libsdl.org)

---

