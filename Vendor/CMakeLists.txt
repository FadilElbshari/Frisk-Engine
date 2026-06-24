include(FetchContent)

# fetch GLFW source code from github
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# fetch GLM source code from github
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)


# glad is a self-vendored dependency
add_subdirectory(glad)

# stb includes no compiled code so it can be declared as an interface
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)