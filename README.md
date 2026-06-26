# SVG Editor

Simple vector graphics editor for a C++ course project.

## Stack

- C++20
- Qt 6 Widgets
- Qt Graphics View Framework
- CMake
- JSON document persistence

## Prerequisites

- CMake 3.24 or newer
- Qt 6 with `Core`, `Gui`, `Widgets`, and `Test`
- Ninja
- A C++20 compiler
  - Windows: MSVC in Developer PowerShell or Developer Command Prompt
  - Linux: Clang or GCC

The current recommended Windows setup is `MSYS2 UCRT64`, which has already been wired into `CMakePresets.json`.

If CMake cannot find Qt automatically in a different environment, set one of these before configure:

```powershell
$env:Qt6_DIR = "C:\path\to\Qt\6.x.x\msvc2022_64\lib\cmake\Qt6"
```

or:

```powershell
$env:Qt6_ROOT = "C:\path\to\Qt\6.x.x\msvc2022_64"
```

## Configure, Build, Test

Windows debug:

```powershell
cmake --preset windows-ucrt64-debug
cmake --build --preset build-ucrt64-debug
ctest --preset test-ucrt64-debug
```

Windows release:

```powershell
cmake --preset windows-ucrt64-release
cmake --build --preset build-ucrt64-release
```

Linux debug:

```bash
cmake --preset linux-debug
cmake --build --preset build-linux-debug
ctest --preset test-linux-debug
```

## Quality Gates

- `ctest` runs the unit tests.
- `cmake --build <build-dir> --target typecheck` performs compile-based type checking.
- `cmake --build <build-dir> --target format` applies `clang-format`.
- `cmake --build <build-dir> --target format-check` verifies formatting.
- `cmake --build <build-dir> --target lint` runs `clang-tidy` when available.

`typecheck` is a compile-based target because C++ performs type validation during compilation.
