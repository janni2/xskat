# Contributing to XSkat

Thank you for your interest in contributing to XSkat! We welcome contributions from the community.

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/your-username/xskat.git
   cd xskat
   ```
3. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Setup

### Prerequisites

- CMake 3.10 or higher
- C99-compatible compiler (GCC, Clang)
- X11 development libraries

### Building

```bash
mkdir build && cd build
cmake ..
make
```

### Testing

Run the executable to test your changes:
```bash
./xskat
```

## Contribution Guidelines

### Code Style

- Follow C99 standards
- Use consistent indentation (spaces preferred)
- Keep line lengths reasonable (under 80-100 characters)
- Use meaningful variable and function names
- Add comments for complex logic

### Commit Messages

- Use clear, descriptive commit messages
- Start with a verb in present tense (e.g., "Add", "Fix", "Update")
- Keep the first line under 50 characters
- Add a detailed description if necessary

Example:
```
Add IRC reconnection feature

- Implement automatic reconnection on connection loss
- Add configurable retry intervals
- Update error handling for network timeouts
```

### Pull Requests

1. **Update documentation** if your changes affect user-facing features
2. **Test thoroughly** on your local system
3. **Provide a clear description** of what your PR does
4. **Reference any related issues** using #issue-number

### What to Contribute

We welcome:
- **Bug fixes** - Help make XSkat more stable
- **Feature improvements** - Enhance existing functionality
- **Documentation** - Improve README, comments, or help text
- **Translations** - Add or improve language support
- **Performance optimizations** - Make the game run better

### What NOT to Contribute

Please avoid:
- Breaking changes without discussion
- Platform-specific code without broad benefit
- Large refactoring without prior discussion
- Changes that significantly alter the user interface without consultation

## Reporting Issues

When reporting bugs:
1. **Use a clear title** that describes the problem
2. **Provide system information** (OS, compiler version, etc.)
3. **Include steps to reproduce** the issue
4. **Attach relevant logs** or error messages

## Code of Conduct

Be respectful and constructive in all interactions. We want XSkat to be welcoming to contributors from all backgrounds.

## Questions?

Feel free to open an issue for questions about contributing or development.

## License

By contributing to XSkat, you agree that your contributions will be licensed under the MIT License.