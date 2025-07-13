cmake_minimum_required(VERSION 3.10)

project(cmake-build-debug/obd_dashboard VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(obd_dashboard
        main.cpp
        src/obd.cpp
        src/bluetooth.cpp
        src/dashboard.cpp
        src/bluetooth.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})
add_definitions(${SDL2_CFLAGS_OTHER})

target_link_libraries(obd_dashboard
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    SDL2_ttf
  )

add_subdirectory(simulator)


