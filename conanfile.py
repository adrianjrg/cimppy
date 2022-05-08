from conan import ConanFile


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"
    default_options = {
        "catch2/*:with_main": True,
    }

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("fmt/8.1.1")

        # Testing only dependencies below
        self.requires("catch2/2.13.8")
