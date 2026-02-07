# ✦ Lux Engine
![Status](https://img.shields.io/badge/Status-In%20Development-yellow?style=for-the-badge&logo=cplusplus)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)
> Multi platform Game Engine being made from scratch in C++

### Platform Support
- [x] Windows (Implementing Win32 Backend)
- [ ] Linux (Planned: X11)
- [ ] macOS (Planned: Cocoa)

### Features
- [x] Multi-Platform Window class
- [x] Inputs (Implementing)
- [x] OpenGL Context
- [x] Time manager class
- [ ] Logger
- [ ] 2D Renderer

### How to Run (Windows)

#### Dependencies
- Python
- CLANG (with a toolchain like MSVC on Windows)

#### Compiling

1. Clone the repository:
```bash
git clone https://github.com/neverevis/Lux
cd Lux
```

2. Change the settings on build.py (Compiler, Debug, Dependencies)
> Planing to make a json configuration in the future

3. Compile and run:
```bash
python build.py
build/bin/sandbox.exe
```
> if you change the BUILD_DIR on the build.py, the second command has to be adjusted to the new path
