# 2dMaze

**2dMaze** is a **C++ Object-Oriented Programming (OOP) project** implemented as a command-line application.  
It allows users to create, save, load, and solve 2D mazes through a simple text-based interface.  
The project demonstrates OOP principles such as **encapsulation, inheritance, polymorphism, and design patterns (MVC & Observer)**.

## Table of Contents

- [Features](#features)  
- [Project Structure](#project-structure)  
- [Requirements](#requirements)  
- [Installation & Build](#installation--build)  
- [Usage](#usage)  
  - [Generating a Maze](#generating-a-maze)  
  - [Saving & Loading](#saving--loading)  
  - [Solving the Maze](#solving-the-maze)  
- [Design & Architecture](#design--architecture)  
  - [Core Components](#core-components)  
  - [Algorithms](#algorithms)  
  - [CLI Design](#cli-design)  
- [Extending the Project](#extending-the-project)  
- [License & Disclaimer](#license--disclaimer)  

---

## Features

- 🌀 **Maze Generation** – Create 2D mazes with customizable size.  
- 💾 **Save & Load** – Persist mazes to files and reload them later.  
- 🧭 **Maze Solving** – Solve mazes using **BFS** and **A*** algorithms.  
- 🏗️ **OOP Design** – Built with modular classes, MVC architecture, and Observer pattern.  
- ⌨️ **Text-Based Interface** – Simple CLI for interacting with the system.  

---

## Project Structure

```
├── Adapter.h
├── Algorithm.h
├── Astar.h
├── BFS.h
├── CLI.h
├── Command.h
├── Controller.h
├── Model.h
├── MyMazeGenerator.h
├── Observer.h
├── Searchable.h
├── SimpleMazeGenerator.h
├── Solution.h
├── View.h
├── maze.h
├── mazeCompression.h
├── mazeGenerator.h
└── main.cpp
```

### Overview

- **CLI & Commands**: `CLI.h`, `Command.h`, `Controller.h` – Handle user input, command parsing, and control flow.  
- **Model & View**: `Model.h`, `View.h` – Data representation (`Model`) and presentation (`View`).  
- **Maze Generation**: `mazeGenerator.h`, `MyMazeGenerator.h`, `SimpleMazeGenerator.h` – Algorithms for maze creation.  
- **Algorithms**: `BFS.h`, `Astar.h`, `Algorithm.h`, `Searchable.h`, `Solution.h` – Implement pathfinding.  
- **Patterns**: `Adapter.h`, `Observer.h` – Ensure decoupled and modular design.  
- **Utility**: `maze.h`, `mazeCompression.h` – Maze data structures and file compression.  

---

## Requirements

- C++17-compatible compiler (e.g., `g++`, `clang++`)  
- Standard C++ library (no external dependencies)  

---

## Installation & Build

Clone the repository:

```bash
git clone https://github.com/eliyasamary/2dMaze.git
cd 2dMaze
```

Compile:

```bash
g++ -std=c++17 main.cpp -o 2dMaze
```

Run the program:

```bash
./2dMaze
```

---

## Usage

### Generating a Maze

```
generate <rows> <cols>
# Example: generate 20 30
```

Creates a maze with 20 rows and 30 columns.

### Saving & Loading

```
save <filename>
load <filename>
```

Save mazes to disk or load them from files.

### Solving the Maze

```
solve <algorithm>
# Options: BFS, Astar
```

Solve the maze using the selected algorithm.

### Other Commands

```
help   # Show available commands
exit   # Quit the application
```

---

## Design & Architecture

### Core Components

- **MVC** – Model, View, Controller separation.  
- **Commands & Adapter** – Extendable command handling and flexible input adaptation.  
- **Observer Pattern** – Notify and update system components reactively.  

### Algorithms

- **BFS** – Guarantees shortest path in unweighted mazes.  
- **A\*** – Uses heuristics for faster solutions in large mazes.  

### CLI Design

- Interactive text interface.  
- Commands dispatched through `Controller`.  
- Extensible design for adding new commands.  

---

## Extending the Project

- Add new pathfinding algorithms (DFS, Dijkstra, IDA\*).  
- Enhance compression and file handling.  
- Build a graphical UI with **SDL** or **ncurses**.  
- Add maze customization (weighted edges, traps, multiple exits).  

---

## License & Disclaimer

This project is for **educational purposes**.  
Feel free to use and modify the code. If re-used in academic or professional work, attribution is appreciated.

---
