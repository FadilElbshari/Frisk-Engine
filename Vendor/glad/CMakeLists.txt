# include glad as a static library and its header file in the include dir
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)