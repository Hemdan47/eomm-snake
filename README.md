# eomm-snake

A simple Snake game built with C++ and Raylib.

## Demo

https://github.com/user-attachments/assets/546ee3c6-1fbf-43b8-ba85-313a1a0c07b6

## Class Diagram

<img width="2024" height="1941" alt="Class Diagram" src="https://github.com/user-attachments/assets/fd1947b1-2868-448b-a2a6-9c13997ceb73" />


## Design

This project uses a small, clean layered design where each class has one clear responsibility.

### 1. Core idea

The game is split into orchestration, input, game rules, entities, and shared configuration:

1. Application controls the app lifecycle and frame loop.
2. Controller translates keyboard input into direction changes.
3. Game owns and updates the game state and rules.
4. Snake and Food represent world entities.
5. Config stores shared settings like board size, colors, and spacing.

This separation keeps rendering, input, and game rules from being tightly coupled.

### 2. Runtime flow

1. The program creates Application and starts run.
2. Application initializes window and target FPS.
3. Application creates Game and enters the render loop.
4. Every frame:
   - Application checks fixed update timing with event_triggered(0.1).
   - If the interval elapsed, Game::update runs one logic tick.
   - Controller reads input and returns a valid next direction.
   - Application writes running and direction back into Game.
   - Application draws UI frame and asks Game to draw entities.
5. On exit, resources are released and window/audio are closed.

This gives smooth rendering while game logic advances at a controlled step.

### 3. State ownership and memory model

1. Application owns Game and Controller using unique_ptr, so lifecycle is explicit and single-owner.
2. Game owns Snake and Food using unique_ptr.
3. Config is shared by reference inside Game, Snake, and Food, so all gameplay and rendering values stay consistent.
4. Game constructor loads audio resources, and destructor unloads them.
5. Food constructor loads texture, and destructor unloads it.

This model avoids accidental copies of heavy resources and keeps cleanup deterministic.

### 4. Game logic design

1. Movement:
   - Snake stores body as deque<Vector2>, head at front.
   - Each update pushes a new head in movement direction.
   - Tail is removed unless food was eaten.

2. Collision pipeline:
   - Check food collision first to determine growth.
   - Move snake.
   - Check wall and tail collisions.
   - If collision happened, call game_over.

3. Random placement:
   - Game generates random grid cells.
   - New food position is regenerated until it does not overlap snake body.

4. Game over handling:
   - Snake resets to initial body and direction.
   - Food gets a valid new position.
   - Running becomes false, score resets, wall sound plays.

This keeps rules predictable and easy to test mentally.

### 5. Input and rule safety

Controller prevents instant reverse direction (for example up to down in one step), which avoids invalid self-collision behavior from direct opposite turns.



## Requirements

- CMake 4.0.2+
- C++ compiler (MSVC, GCC, or Clang)
- Git

## Install and Build

```bash
git clone https://github.com/Hemdan47/eomm-snake.git
cd eomm-snake
cmake -S . -B build
cmake --build build
```

Raylib is downloaded automatically by CMake.

## Run

### Windows

```bash
.\build\bin\eomm_snake.exe
```

### Linux/macOS

```bash
./build/bin/eomm_snake
```
