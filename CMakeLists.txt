# Copy the font file to the same directory as the binary
# configure_file(OpenSans-Regular.ttf OpenSans-Regular.ttf COPYONLY)



cmake_minimum_required(VERSION 3.10)
project(SFML_Interface)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(sfml_app main.cpp)

target_link_libraries(sfml_app sfml-graphics sfml-window sfml-system)

    