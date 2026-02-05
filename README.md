# Maze Game (C)

A command-line maze program written in **C** that loads mazes from text files, validates them, and runs the maze logic end-to-end (including handling invalid inputs gracefully). The repository includes multiple test mazes covering normal cases and edge cases (bad dimensions, invalid characters, open/closed mazes, etc.). :contentReference[oaicite:1]{index=1}

---

## Features

- Loads maze layouts from input files (e.g., `5x5.in`, `15x9.txt`) :contentReference[oaicite:2]{index=2}  
- Strong input validation (dimensions, malformed grids, unexpected characters, invalid structures) using dedicated “bad” test files :contentReference[oaicite:3]{index=3}  
- Includes a set of sample and failure-case test files for quick verification (`bad_width.txt`, `bad_height.txt`, `invalid_chars_5x5.txt`, etc.) :contentReference[oaicite:4]{index=4}  
-  Build automation via `makefile` :contentReference[oaicite:5]{index=5}  

---

## Project Structure

- `maze.c` — main implementation :contentReference[oaicite:6]{index=6}  
- `makefile` — build rules :contentReference[oaicite:7]{index=7}  
- `*.in` / `*.txt` — sample mazes + negative tests (invalid width/height, invalid chars, open/closed cases, etc.) :contentReference[oaicite:8]{index=8}  

---

## Build & Run

### Build
```bash
make
