# SushiGo.cpp

A terminal-based remake of the card game **Sushi Go!**, developed in C++ using object-oriented design and a custom dynamic array class. This project models multi-round, multi-player card drafting with full game logic, rule enforcement, and color-rendered ASCII graphics in the terminal.

## Features

- Complete 3-player implementation with drafting, rotation, and scoring
- Modular structure across ~30 C++ source files
- Custom `Vector` class with dynamic memory management
- Colorized terminal interface using ANSI escape codes
- Rule support for chopsticks, wasabi multipliers, maki rolls, puddings, and more
- Handles round transitions, tie logic, and full score calculation

## Background

This project was developed to simulate a real-world, multi-file C++ application with robust abstractions, dynamic memory control, and structured game logic. It emphasizes modular design, real-time terminal interaction, and core software engineering practices — all without third-party libraries.

**Sushi Go!** is a turn-based card drafting game where players build point-scoring combinations of sushi dishes across multiple rounds. Players simultaneously choose cards from a rotating hand, aiming to optimize combinations (e.g., pairs of tempura, highest maki rolls, dumpling chains) while anticipating opponents’ strategies. The game rewards timing, memory, and planning over three rounds.

## Core Components

- `card.*` – Defines card types and behavior
- `player.*` – Tracks hand, board state, and score for each player
- `game.*` – Controls turn order, round transitions, and overall logic
- `board.*` – Handles card rendering and positioning in the terminal
- `vector.*` – Custom dynamic array for storing card pointers
- `termfuncs.*` – Terminal formatting, screen control, and cursor logic
