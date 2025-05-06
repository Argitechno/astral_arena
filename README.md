# Astral Arena

A space-themed arena game built with C++ and SFML as the final project for CS151.

## 🎮 Game Description
Navigate the main menu to start a match, select ships, change maps, and adjust match settings. The game launches into an asteroid-filled arena rendered using SFML.

## 👨‍👨‍👦 Team Members
- Caleb Blondell – Player mechanics and ship handling
- Justin Keimer – Map and object rendering
- Will Hall – Menu system, UI logic, integration


## ✅ Features
- Interactive menu with keyboard controls
- Seamless launch into game mode
- Modular structure (maps, players, menu separated)
- SFML graphics engine

## 🛠️ How to Compile and Run

```bash
g++ -std=c++17 main.cpp menu.cpp map.cpp block.cpp asteroid.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
./game
