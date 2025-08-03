# XSkat

XSkat is a free implementation of the classic German card game Skat, following the official Skat Order rules. The game supports up to 3 players with computer opponents providing challenging gameplay.

## Features

- Complete implementation of Skat rules according to the official Skat Order
- Up to 3 computer-controlled players with AI
- X11-based graphical interface
- IRC connectivity for online play
- Multiple language support (English/German)

## Requirements

- CMake 3.10 or higher
- C99-compatible compiler (GCC, Clang)
- X11 development libraries
- Linux/Unix environment

## Building from Source

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd xskat
   ```

2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

3. Configure with CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   make
   ```

5. Run the game:
   ```bash
   ./xskat
   ```

## Installation

### Ubuntu/Debian
```bash
sudo apt-get install libx11-dev cmake build-essential
```

### Fedora/CentOS
```bash
sudo dnf install libX11-devel cmake gcc make
```

## Usage

Simply run `./xskat` to start the game. The interface is intuitive with mouse and keyboard controls.

For detailed installation instructions, see the [INSTALL](INSTALL) file.

## Documentation

- [INSTALL](INSTALL) - Detailed installation instructions
- [CHANGES](CHANGES) - Version history and changelog
- Man pages: `xskat.man` and `xskat-de.man`

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

Originally created by Gunter Gerhardt  
Website: http://www.xskat.de

## Acknowledgments

- Based on the official Skat Order rules
- Uses X11 for graphics rendering
- IRC functionality for online multiplayer