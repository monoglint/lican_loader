cmake_minimum_required(VERSION 3.10)
project(licanc_loader VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(licanc)

add_executable(licanc_loader
    src/main.cc
)

target_link_libraries(licanc_loader PRIVATE licanc)

set_target_properties(licanc_loader PROPERTIES
    OUTPUT_NAME "licanc"
)