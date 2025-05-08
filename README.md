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
- **Credits screen** with animated scroll and attribution

## 🛠 How to Build and Run

This project runs on **Linux**, **Windows (via Git Bash, WSL, or MinGW)**, and **Mac** — no special environment needed.  
No CMake or Visual Studio required.

### ✅ Prerequisites
- g++ with C++17 support
- SFML installed (graphics, window, system, audio)
- All asset files placed under the `/assets/` directory


### 🚀 To Compile and Run:

From the root of the repo:

```bash
g++ -std=c++17 -Iinclude src/*.cpp src/submenu/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game
./game
```

## Assets & Attribution

- **Font:** Arial (System)
- **Sound Effects:** Freesound.org (placeholder .wav files)
- **Background Image:** Custom/placeholder artwork used under fair use (student project)


## Future Work / Extensions

- [ ] Fully implement player logic and collision
- [ ] Add animated ship selection menu
- [ ] Multiple map styles with scroll selection
- [ ] Local multiplayer round tracking
- [ ] Settings menu (audio sliders, fullscreen toggle)
