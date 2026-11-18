# C17 starter — Conan 2 + CMake + Ninja + GCC

A small C17 project that builds a native `Hello World!` executable.

## What each tool does

| Tool | Role in this project |
| --- | --- |
| Conan 2 | Detects your compiler settings, manages any dependencies you add, and writes CMake presets and a toolchain file. |
| CMake | Reads `CMakeLists.txt` and generates Ninja build rules from the selected preset. |
| Ninja | Runs the build rules and recompiles files affected by your changes. |
| GCC | Compiles and links the C code into executables. |
| CTest | Runs the tests registered in `CMakeLists.txt`. It comes with CMake. |
| GDB | Pauses a running program at a breakpoint so you can step through its source and inspect its state. |

## Install and check the tools

You can install the system tools using this command:

```bash
curl -fsSL https://subhajitpaul.com/ctools.sh | bash
```

If you already have the tools, check their versions. You need Conan 2.x and
CMake 3.23 or newer. GDB is needed for the debugging exercise.

```bash
conan --version
cmake --version
ninja --version
gcc --version
gdb --version
```

## Build, run, and test

From the project root, create a default Conan profile once if you do not
already have one. Conan uses this profile to record settings such as your
operating system, architecture, and compiler.

```bash
conan profile detect
```

Then install the Conan configuration, configure CMake, and build.

```bash
conan install . --build=missing -s build_type=Debug \
  -c tools.cmake.cmaketoolchain:generator=Ninja
cmake --preset conan-debug
cmake --build --preset conan-debug
```

1. `conan install .` reads `conanfile.py` from the current directory and
   generates the CMake toolchain and presets. If you add dependencies later,
   `--build=missing` lets Conan build packages that have no matching binary.
2. `cmake --preset conan-debug` configures `build/Debug` and writes the Ninja
   build rules. The preset selects the Debug build, which includes information
   GDB uses to show source lines.
3. `cmake --build --preset conan-debug` invokes Ninja to compile and link
   `demo` and `test_main`.

Run the program and then the tests.

```bash
./build/Debug/demo
ctest --test-dir build/Debug --output-on-failure
```

The demo prints `Hello World!` without a trailing newline, so your shell prompt
may appear on the same line. CTest runs the `starter_tests` entry and reports
one passing test. That entry runs `tests/test_main.c`'s two example checks
through the `test_main` executable. A failed check prints a message and returns
a failure exit status, which CTest displays with `--output-on-failure`.

After editing a `.c` or `.h` file, rerun the build command and then the program
or tests. If you change Conan dependencies or settings, rerun all three build
commands.

### Build a Release version

Use Release for an optimized build. The Debug executable stays in its own
build directory.

```bash
conan install . --build=missing -s build_type=Release \
  -c tools.cmake.cmaketoolchain:generator=Ninja
cmake --preset conan-release
cmake --build --preset conan-release
ctest --test-dir build/Release --output-on-failure
./build/Release/demo
```

### Common setup errors

- **Conan cannot find the default profile.** Run `conan profile detect`.
- **CMake cannot find `conan-debug`.** Run the Debug `conan install` command
  from the project root, then check the available presets with
  `cmake --list-presets`.
- **CMake reports that the generator does not match the previous one.** Move
  the affected build directory (`build/Debug` or `build/Release`) aside, then
  rerun Conan install, CMake configure, and CMake build for that configuration.

See the [Conan Ninja generator example](https://docs.conan.io/2.30/examples/tools/cmake/cmake_toolchain/use_different_toolchain_generator.html)
for more about how Conan selects Ninja.

## Debug with GDB

Build the Debug version first, then launch GDB from the project root.

```bash
gdb ./build/Debug/demo
```

Enter these commands at the `(gdb)` prompt.

| Command | What happens |
| --- | --- |
| `break main` | Set a breakpoint in `main` in `src/main.c`. |
| `run` | Start the program and pause before it prints. |
| `next` | Execute the current line and stop at the next one, stepping over function calls. |
| `backtrace` | Show the chain of active function calls. |
| `continue` | Resume execution. The demo exits normally. |
| `quit` | Return to your shell. |

For an exercise with local variables, open `gdb ./build/Debug/test_main`. Enter
`break main` and `run`, then use `next` until GDB shows the `for` loop.
Enter `print total` to see 0. Enter `until tests/test_main.c:11` to run up to
the `if (total != 12)` check, then use `print total` again to see 12.
For more commands, see the
[GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb.html).

## What C headers do

A header is usually a `.h` file that shares declarations, types, and macros
with one or more `.c` source files. During compilation, the preprocessor
substitutes the header's contents where you write `#include`.

| Example | What it provides here |
| --- | --- |
| `#include <stdio.h>` | The C standard library declarations for input and output functions such as `printf`, used by the demo. |
| `#include <stdlib.h>` | C standard library utilities and the `EXIT_SUCCESS` and `EXIT_FAILURE` constants used by the tests. |
| `#include <string.h>` | C standard library string functions such as `strlen`, used by the string-length check. |

Angle brackets are conventional for standard and installed library headers.
Quotes are conventional for project headers. In this starter, CMake exposes
`include/` to both executables. The directory starts empty. Git does not
track empty directories, so run `mkdir -p include` in a fresh checkout when
you are ready to add a header.

For example, if you add `include/math_utils.h` with a declaration such as
`int add(int a, int b);`, a source file can use `#include "math_utils.h"` to
see that declaration. Put the function body in a `.c` file and add that file
to the CMake target that calls it. An include guard, typically an
`#ifndef`, `#define`, and closing `#endif`, keeps a header from being
processed twice when compiling the same source file.

## Start a new project with `conan new`

From the root of this checkout, register the starter under your Conan 2 home
directory. The final directory name is the template name you pass to `conan new`.

```bash
template_dir="$(conan config home)/templates/command/new/c-starter-conan2"
mkdir -p "$template_dir"
cp -R CMakeLists.txt conanfile.py src tests LICENSE README.md \
  .clang-format .gitignore .github "$template_dir/"
```

From the directory where you want to create your new project, run the
following commands.

```bash
mkdir my-c-project
cd my-c-project
conan new c-starter-conan2
mkdir -p include
```

The generated files use the starter's defaults. To rename the project, edit
`name` in `conanfile.py` and `project(...)` in `CMakeLists.txt`. Follow the
build steps above from the new project root.
