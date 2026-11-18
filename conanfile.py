from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Starter(ConanFile):
    name = "c-starter"
    version = "0.1.0"
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    # To add an external dependency:
    # def requirements(self):
    #     self.requires("zlib/1.3.1")
    # Then find_package(ZLIB REQUIRED) and link ZLIB::ZLIB in CMake.
