# 🍓 Celeste Clone

> A fan-made recreation of Celeste's core movement and mechanics, built in C++ with Raylib.

![Language](https://img.shields.io/badge/language-C++-blue)
![Library](https://img.shields.io/badge/library-Raylib-orange)
![Status](https://img.shields.io/badge/status-in%20progress-yellow)

---

## 📸 Preview

> *Madeline runs, jumps, dashes and wall-grabs through a tile-based platformer level.*

---

## 📖 Description

This project is a **personal recreation of Celeste** (the indie platformer by Maddy Thorson & Noel Berry), built from scratch in **C++17** using the **Raylib** graphics library.

The focus is on faithfully replicating Celeste's signature movement feel: tight controls, precise dash mechanics, wall grabbing, and animated sprites — all in a tile-based map system.

---

## ✨ Features

- 🏃 **Tight platformer movement** — walk, run, jump with variable height
- 💨 **Dash mechanic** — directional dash with 1 dash per air phase
- 🧗 **Wall grab & wall slide** — climb walls while holding Space
- 🎬 **Sprite animations** — multiple spritesheets for each state (idle, run, jump, dash, wall grab)
- 📷 **Smooth camera** — eased transitions with configurable threshold
- 🗺️ **Tile-based map** — loaded from a `.txt` file, simple `#` / space format
- 🔲 **Debug hitbox mode** — toggle with `H`
- 🖥️ **Adaptive resolution** — auto-scales tile size to monitor resolution

---

## 🗂️ Project Structure

```
celeste/
├── src/
│   ├── main.cpp        # Entry point, window & game loop
│   ├── player.cpp      # Physics, collision, jump, dash
│   ├── animation.cpp   # Sprite rendering logic
│   ├── handle.cpp      # Input handling
│   ├── camera.cpp      # Camera transitions
│   └── map.cpp         # Map loading & tile rendering
├── includes/
│   ├── player.hpp
│   └── map.hpp
├── images/             # Spritesheets
├── map/
│   └── map.txt         # Level layout
└── Makefile
```

---

## 🚀 Getting Started

### Requirements

- Linux (Ubuntu 20.04+ recommended)
- `g++`, `make`, `cmake`

### Build & Run

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/celeste-clone.git
cd celeste-clone

# Build (Raylib is cloned and compiled automatically)
make

# Run the game
./Celeste
```

> Raylib is automatically cloned from GitHub and compiled as a static library on first build. No manual installation needed.

---

## 🗺️ Map Format

Maps are plain `.txt` files:

```
#############
#           #
#   ####    #
#        P  #
#############
```

| Symbol | Meaning |
|--------|---------|
| `#`    | Solid tile (wall/ground) |
| ` `    | Empty space |
| `P`    | Player spawn point |

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `← →` | Move left / right |
| `↑` | Jump (hold for higher jump) |
| `↓` | Fast fall |
| `Shift` | Dash |
| `Space` | Wall grab (hold near wall) |
| `H` | Toggle hitbox debug view |
| `F11` | Toggle fullscreen |
| `ESC` | Quit |

---

## 🏗️ Technical Highlights

- **Physics system** — custom gravity, variable jump height via hold timer, velocity-based movement
- **Collision detection** — AABB hitbox with tile-based grid queries, separate X/Y axis resolution
- **Wall detection** — directional raycasting along player edges for left/right wall detection
- **Eased camera** — cubic ease-in/out interpolation for smooth screen transitions
- **State machine** — animation state driven by physics state (grounded, airborne, dashing, wall-grabbing)

---

## 👤 Author

- **Mathéo Vachon** — *École 42 Lyon* — [@mvachon](https://github.com/YOUR_USERNAME)

---

## 📚 Inspiration

- [Celeste](https://www.celestegame.com/) by Maddy Thorson & Noel Berry
- [Celeste movement breakdown](https://maddythorson.medium.com/celeste-and-towerfall-physics-d24a2eb30d43) — Maddy Thorson's own writeup on the game's physics
