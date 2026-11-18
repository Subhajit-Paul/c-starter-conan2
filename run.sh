conan install . --build=missing -s build_type=Debug \
  -c tools.cmake.cmaketoolchain:generator=Ninja
cmake --preset conan-debug
cmake --build --preset conan-debug
./build/Debug/executable
