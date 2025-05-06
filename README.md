# Astral Arena

Astral Arena is a top-down space dueling game developed as a CS151 final group project. The focus of this repo is the complete menu system, written in C++ using SFML.

## 🧩 Team Roles

- **Caleb Blondell** – Player logic and ship behavior (pending integration)  
- **Justin Keimer** – Map design, arena layout, and collision logic  
- **Will Hall** – Menu System, UI polish, sound integration, ESC logic, submenus, credits, README  


## 🎮 Menu Features

- Animated **scrolling space background**
- **Glow-pulsing title** (“Astral Arena”)
- **ESC hold-to-exit** logic (2-second delay, with visual hint)
- Keyboard navigation:
  - `[W]/[S]` or `[↑]/[↓]` to move
  - `[Enter]` to select
  - `[←]/[→]` on specific items to adjust
- **Match Count** selection (odd-only: 1, 3, 5…)
- **Sound: On/Off** toggle with live effect
- **Select Map / Ship** stub menus (styled placeholders)
- Full **Credits screen** with animated scroll and attribution

## 🛠 How to Build and Run

### Requirements:
- SFML 2.5.x (graphics, window, audio modules)
- g++ with C++17 support

### Compile command:

```bash
g++ -std=c++17 main.cpp menu.cpp map.cpp block.cpp asteroid.cpp submenu/deadmenu.cpp submenu/creditsmenu.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game
```

Then run:
```bash
./game
```
