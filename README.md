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

## Requirements
- **CMake** (>=3.x)
- **C++ Compiler** (C++11 or later)
- **SFML** (for graphics)
- **Build System**: `make`, `MSYS2`, or **Visual Studio** (for Windows)

## Building (Linux & Windows)

### 1. Clone the repository:
```bash
git clone https://github.com/Argitechno/astral_arena.git
cd astral_arena
```

### 2. Create the build directory:
```bash
mkdir build
cd build
```

### 3. Configure the project with CMake:
#### For Linux/Windows (MinGW/MSYS2):
```bash
cmake ..
```
#### For Windows (Visual Studio):
```bash
cmake -G "Visual Studio 16 2019" ..
```

### 4. Build the project:
#### On Linux or MinGW/MSYS2:
```bash
make
```
#### On Windows (Visual Studio):
- Open the generated `.sln` file in Visual Studio and build the project.

### 5. Run the project:
```bash
./bin/AstralArena
```
or
```bash
./bin/AstralArena
```

## Cleaning

To clean the build files:
```bash
make clean
```
Or delete the build directory:
```bash
rm -rf build
```

## Notes
- Ensure SFML is installed and properly linked.
- On Windows, use MinGW/MSYS2 or Visual Studio to build.
- Adjust CMakeLists.txt if additional dependencies are needed.

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
