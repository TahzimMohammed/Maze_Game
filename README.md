# Maze Game (C)

A command-line maze program written in **C** that loads mazes from text files, validates them, and runs the maze logic end-to-end (including handling invalid inputs gracefully). The repository includes multiple test mazes covering normal cases and edge cases (bad dimensions, invalid characters, open/closed mazes, etc.). 

---

## Features

- Loads maze layouts from input files (e.g., `5x5.in`, `15x9.txt`) 
- Strong input validation (dimensions, malformed grids, unexpected characters, invalid structures) using dedicated “bad” test files 
- Includes a set of sample and failure-case test files for quick verification (`bad_width.txt`, `bad_height.txt`, `invalid_chars_5x5.txt`, etc.)
-  Build automation via `makefile` 
---

## Project Structure

- `maze.c` — main implementation :contentReference
- `makefile` — build rules :contentReference
- `*.in` / `*.txt` — sample mazes + negative tests (invalid width/height, invalid chars, open/closed cases, etc.) 

---

## Build & Run

### Build
```bash
make
