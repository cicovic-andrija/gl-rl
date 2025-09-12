cmake_minimum_required(VERSION 3.15)

project(cgl-rl CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(cgl-rl ${SRC_FILES})

add_library(raylib STATIC IMPORTED)
set_target_properties(
    raylib PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libraylib.a"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include"
    INTERFACE_LINK_LIBRARIES "m;pthread;dl;rt;GL;X11"
)

target_link_libraries(cgl-rl PRIVATE raylib)
