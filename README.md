# C17 starter — Conan 2 + CMake + Ninja + GCC

A deliberately small C project template for Python developers coming back to C.
This is **not** Python-to-C compilation or Cython. The `pyc.h` helpers are plain
C17, so GCC produces a normal native executable with no Python dependency.

## Contents

- `include/pyc.h` — `print(x)` (one argument), `pyc_input(prompt)` (caller frees
  returned string), and `PYC_VECTOR(Type, Name)` (typed dynamic array).
- `src/main.c` — example including struct-based "class".
- `tests/test_pyc.c` — lightweight test executable.
- `conanfile.py` — Conan 2 project integration; **no third-party packages yet**.
- `CMakeLists.txt` — CMake build and CTest tests using Ninja.

## Start a new project with `conan new`

From the root of this checkout, register the starter under your Conan 2 home
directory. The final directory name is the template name you pass to `conan new`.

```bash
template_dir="$(conan config home)/templates/command/new/c-starter-conan2"
mkdir -p "$template_dir"
cp -R CMakeLists.txt conanfile.py include src tests LICENSE README.md \
  .clang-format .gitignore .github "$template_dir/"
```

From the directory where you want to create your new project, run:

```bash
mkdir my-c-project
cd my-c-project
conan new c-starter-conan2
```

The generated files use the starter's defaults. To rename the project, edit
`name` in `conanfile.py` and `project(...)` in `CMakeLists.txt`. If you haven't
set up a default Conan profile yet, run `conan profile detect`, then follow the
build steps below.

## Build with Conan 2

```bash
conan install . --build=missing -s build_type=Debug
cmake --preset conan-debug
cmake --build --preset conan-debug
ctest --test-dir build/Debug --output-on-failure
./build/Debug/demo
```

With `cmake_layout`, Conan generates the user presets and the `build/Debug`
build tree. Use `conan-release` and `build/Release` for Release builds.
