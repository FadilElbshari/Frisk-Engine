# determine wether to link as shared (DLL) or static
if(ENGINE_BUILD_SHARED)
    set(ENGINE_LIB_TYPE SHARED)
else()
    set(ENGINE_LIB_TYPE STATIC)
endif()

# collect all source files within the directory
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# compile the source code into a library depending on the linking type
add_library(Engine ${ENGINE_LIB_TYPE} ${ENGINE_SOURCES})

# add include directories for public scope
target_include_directories(Engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# add local include directories (local .h header files)
target_include_directories(Engine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# ensure target compiles with C++20
target_compile_features(Engine PUBLIC cxx_std_20)

# define compile macros for shared build
if(ENGINE_LIB_TYPE STREQUAL "SHARED")
    target_compile_definitions(Engine PRIVATE ENGINE_BUILD_DLL)
    target_compile_definitions(Engine PUBLIC ENGINE_BUILD_SHARED)
endif()

# linking against used libraries
target_link_libraries(Engine PUBLIC
    glfw
    glm
    glad
    stb
)