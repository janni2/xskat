# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

XSkat is a classic German Skat card game implementation written in C99. It's an X11-based GUI application with IRC connectivity for online multiplayer, supporting up to 3 players with AI opponents.

## Build Commands

### Standard Development Build
```bash
mkdir build && cd build
cmake ..
make
```

### Debug Build
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Build
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Run the Game
```bash
cd build
./xskat
```

### Installation
```bash
make install
```

## Code Architecture

### Layered Architecture

The codebase has been organized into a clean layered architecture:

**Domain Layer** (`src/domain/`, `include/domain/`):
- `skat_game.c/h` - Core game logic and card handling (ready for integration)
- Infrastructure prepared for pure game logic without dependencies

**Application Layer** (`src/application/`, `include/application/`):
- `settings.c/h` - Centralized settings and configuration management
- Ready for additional business services (i18n, networking)

**Current Source Organization**:
- `src/skat.c` - Main application entry point and core game logic
- `src/null.c` - Null game variant (candidate for domain layer)
- `src/ramsch.c` - Ramsch game variant (candidate for domain layer)  
- `src/xio.c` - X11 window management (candidate for UI layer)
- `src/xdial.c` - Dialog management (candidate for UI layer)
- `src/bitmaps.c` + `cards.c` - Graphics assets (candidates for UI layer)
- `src/irc.c` - Network communication (candidate for application layer)
- `src/text.c` - Internationalization (candidate for application layer)

The layered structure provides a clear migration path for progressive refactoring while maintaining full functionality.

### Global State Management

The codebase uses a traditional C approach with extensive global variables defined in `include/skat.h`. Key global arrays and structures:
- Game state: `phase`, `geber`, `spieler`, `trumpf`
- Card management: `cards[32]`, `inhand[4][8]` 
- Player configuration: `strateg[3]`, `hints[3]`, `lang[3]`
- Scoring: `sum[3][3]`, `splsum[3][3]`

### Game States

The game uses a phase-based state machine defined in enum (lines 50-63 of skat.h):
- GEBEN (dealing), REIZEN (bidding), HANDSPIEL, DRUECKEN (card exchange)
- ANSAGEN (announcements), SPIELEN (playing), RESULT

### Key Data Structures

- Player hands stored in `inhand[4][8]` array
- Card values defined by constants: AS, ZEHN, KOENIG, DAME, BUBE, etc.
- Game configuration through multiple arrays (e.g., `blatt[3]`, `strateg[3]`)

### Build System

Uses CMake with:
- C99 standard enforcement
- X11 library dependency
- Conditional compile flags for Debug/Release
- CPack integration for packaging
- Manual pages installation

## Development Notes

- The codebase follows older C conventions with K&R-style function declarations
- Extensive use of global variables for game state
- X11-specific graphics code concentrated in xio.c
- IRC functionality is self-contained in irc.c
- Text localization system supports English/German