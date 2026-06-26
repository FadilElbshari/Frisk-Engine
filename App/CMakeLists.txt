# collect all source files within the directory
file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE APP_HEADERS
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(App
    ${APP_SOURCES}
    ${APP_HEADERS}
)

target_include_directories(App PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(App PRIVATE Engine)

# copy Engine's DLL next to App.exe when Engine is built SHARED (Debug)
if(ENGINE_BUILD_SHARED AND WIN32)
    add_custom_command(TARGET App POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine> $<TARGET_FILE_DIR:App>
    )
endif()