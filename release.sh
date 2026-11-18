conan install . --build=missing -s build_type=Release \
  -c tools.cmake.cmaketoolchain:generator=Ninja
cmake --preset conan-release
cmake --build --preset conan-release
ctest --test-dir build/Release --output-on-failure
./build/Release/executable
