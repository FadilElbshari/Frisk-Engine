# assign minimum required cmake version
cmake_minimum_required(VERSION 3.31)

# define the main project
project(Frisk LANGUAGES CXX C) # specifically C++ project (CXX)

# set required C++ version to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # ensure portability by disallowing compiler specific extensions

# options that are set by presets defined in CMakePresets.json
option(ENGINE_BUILD_SHARED "build engine as shader lib (DLL)" OFF)
option(ENGINE_DIST "disable all dev tools within code" OFF)

# ensure all binaries including EXEs LIBs and DLLs are in one place
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# proceed to subdirectories and run relavent build code
add_subdirectory(Vendor) # first as it includes dependencies required by custom engine code
add_subdirectory(FriskEngine)
add_subdirectory(LearnOpenGL)
#add_subdirectory(App)
