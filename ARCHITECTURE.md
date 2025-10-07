# XSkat Layered Architecture

## Overview

XSkat has been refactored into a clean layered architecture that separates concerns and improves maintainability. The architecture follows the principles of Domain-Driven Design with clear separation between business logic, application services, and user interface.

## Architecture Layers

### Domain Layer (`src/domain/`, `include/domain/`)

**Purpose**: Pure game logic and rules implementation

**Characteristics**:
- Contains core Skat game rules and logic
- No dependencies on UI or external services  
- Functions are deterministic and testable
- Implements official Skat card game rules

**Current Components**:
- `null.c/null.h` - Null game variant logic
- `game_rules.h` - Unified domain API (interface)

**Future Expansions**:
- Core Skat game rules extraction
- Card evaluation and scoring logic
- Pure game state validation

### Application Layer (`src/application/`, `include/application/`)

**Purpose**: Business services and coordination logic

**Characteristics**:
- Orchestrates business logic and services
- Manages external dependencies (network, files)
- Coordinates between domain and UI layers
- Handles cross-cutting concerns

**Current Components**:
- `settings.c/settings.h` - Game configuration management
- `text.c/text.h` - Internationalization and localization
- `irc.c/irc.h` - Network communication services
- `ramsch.c/ramsch.h` - Ramsch game variant coordination
- `game_services.h` - Unified application services API

### UI Layer (`src/ui/`, `include/ui/`)

**Purpose**: User interface and presentation logic

**Characteristics**:
- Handles all user interaction and visual presentation
- Uses X11 for windowing and graphics
- Translates user actions into business events
- Event-driven architecture

**Current Components**:
- `xio.c/xio.h` - X11 window management and event handling
- `xdial.c/xdial.h` - Dialog management and user interaction
- `bitmaps.c/bitmaps.h` - Graphics assets and card rendering
- `cards.c` - Card graphics data (included in bitmaps.c)
- `presentation.h` - Unified UI API

### Main Application (`src/skat.c`)

**Purpose**: Composition root and main orchestrator

**Characteristics**:
- Coordinates all layers and manages overall game flow
- Acts as dependency injection composition root
- Contains main game loop and coordination logic
- Organized into clear functional sections for maintainability

**Structure**:
- **Main Entry Point**: Clean main() function that initializes and starts the game
- **Core Utilities**: Basic utility functions (left, right, swap, random number generation)
- **File I/O and Error Handling**: Configuration and game state persistence
- **Game Logic and Card Evaluation**: Core Skat game mechanics
- **Game Phase Handlers**: Manages different phases of the game (dealing, bidding, playing)
- **Computer AI and Strategy**: Computer player logic and decision making

## Interface Contracts

### Layer Interfaces

- `game_interfaces.h` - Unified interface to all architectural layers
- `core_utils.h` - Core utility functions shared across layers

### Domain Interfaces

- `domain/game_rules.h` - Unified domain layer API
- `domain/null.h` - Null game variant interface

### Application Interfaces

- `application/game_services.h` - Business services API
- Individual service headers for specific functionality

### UI Interfaces

- `ui/presentation.h` - Presentation layer API
- Individual component headers for specific UI concerns

## Build System

The CMakeLists.txt is organized by architectural layers:

```cmake
# Domain Layer: Pure game logic
set(DOMAIN_SOURCES
    src/domain/null.c
)

# Application Layer: Business services
set(APPLICATION_SOURCES
    src/application/settings.c
    src/application/irc.c
    src/application/text.c
    src/application/ramsch.c
)

# UI Layer: Presentation logic
set(UI_SOURCES
    src/ui/bitmaps.c
    src/ui/xio.c
    src/ui/xdial.c
)

# Main application orchestrator
set(CORE_SOURCES
    src/skat.c
)
```

## Migration Status

### ✅ Completed Extractions

- **Null game logic** → Domain layer
- **Settings management** → Application layer
- **IRC networking** → Application layer
- **Internationalization** → Application layer
- **Ramsch game variant** → Application layer
- **Graphics and UI components** → UI layer
- **Dialog management** → UI layer
- **Window management** → UI layer

### 🔄 Future Improvements

- Extract core Skat game rules to domain layer
- Create game state management service
- Implement proper dependency injection
- Add comprehensive unit tests for domain layer
- Create abstractions for external dependencies

## Design Principles

1. **Separation of Concerns**: Each layer has distinct responsibilities
2. **Dependency Direction**: Dependencies flow inward (UI → Application → Domain)
3. **Testability**: Domain layer is fully testable without dependencies
4. **Modularity**: Components are organized by architectural concern
5. **Interface Segregation**: Clear contracts between layers
6. **Open/Closed Principle**: Easy to extend without modifying existing code

## Benefits

- **Maintainability**: Clear separation makes code easier to understand and modify
- **Testability**: Domain logic can be tested independently
- **Extensibility**: New features can be added without affecting other layers
- **Portability**: UI layer can be replaced without changing business logic
- **Code Organization**: Related functionality is grouped logically

## Development Guidelines

1. **Domain Layer**: Keep functions pure and stateless when possible
2. **Application Layer**: Coordinate services but avoid UI dependencies
3. **UI Layer**: Handle presentation concerns only, delegate business logic
4. **Main Application**: Act as orchestrator, avoid implementing business logic

## Main Application Organization

The `src/skat.c` file has been reorganized with a clean structure:

### Entry Point
```c
int main(int argc, char* argv[]) {
    // Initialize random seed for game
    setrnd(&seed[0], savseed = time((time_t*)0));
    
    // Initialize X11 UI system and process command line arguments
    xinit(theargc = argc, theargv = argv);
    
    // Start main game loop
    play();
    
    // Clean application exit
    exitus(0);
    return 0;
}
```

### Functional Sections
- **Main Entry Point**: Minimal, clean initialization and game startup
- **Core Utilities**: Player positioning, swapping, random number generation
- **File I/O and Error Handling**: Configuration persistence and error reporting
- **Game Logic and Card Evaluation**: Card shuffling, hand evaluation, game rules
- **Game Phase Handlers**: Dealing, bidding, playing phases
- **Computer AI and Strategy**: Computer player decision making

### Future Improvements
While the current organization maintains all functionality, future iterations could:
- Extract more utility functions to a dedicated utils module
- Move AI logic to a separate AI service in the application layer
- Create more granular game state management
- Implement proper dependency injection for better testability

This architecture provides a solid foundation for maintaining and extending XSkat while preserving its existing functionality.