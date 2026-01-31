# Rock–Paper–Scissors Tournament (C)

A console-based **Rock–Paper–Scissors Tournament game** implemented in C.  
The player competes against multiple AI opponents, each with a different playing strategy.  
The game also maintains a persistent leaderboard using file handling.

---

## Features

- Single-player tournament mode
- Four AI opponents with different personalities:
  - Random strategy
  - Aggressive strategy
  - Defensive strategy
- Tournament-style progression
- Persistent leaderboard stored in a file
- Win percentage calculation
- Simple menu-driven interface

---

## AI Personalities

| AI Name     | Strategy Type | Description |
|------------|--------------|-------------|
| RandoBot   | Random       | Chooses Rock, Paper, or Scissors randomly |
| Rocko      | Aggressive   | Prefers Rock more frequently |
| Paperina   | Defensive    | Prefers Paper and Scissors |
| Scissorix  | Defensive    | Defensive strategy with higher difficulty |

---

## Game Rules

- Rock beats Scissors
- Scissors beats Paper
- Paper beats Rock
- Same choices result in a tie

Each match consists of one round against an AI opponent.

---

## Menu Options

1. **Play Tournament**  
   Enter your name and compete against all AI opponents.
2. **View Leaderboard**  
   Displays players ranked by win percentage.
3. **Quit**  
   Exits the game and saves leaderboard data.

---

## File Handling

- The leaderboard is stored in a file named `leaderboard.txt`
- Player name, total wins, and total games are saved
- Data is loaded automatically when the program starts

---

## How to Compile and Run

### Compile
```bash
gcc rps_tournament.c -o rps

