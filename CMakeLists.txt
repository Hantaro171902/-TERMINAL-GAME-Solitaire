cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TerminalSolitaire VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and header files
set(SOURCES
    src/main.cpp
    src/ultils.cpp
    src/color.cpp
    src/klondike.cpp
    src/renderer.cpp
)

set(HEADERS
    src/headers/ultils.hpp
    src/headers/color.hpp
    src/headers/klondike.hpp
    src/headers/renderer.hpp
    src/headers/card.hpp
    src/headers/deck.hpp
    src/headers/pile.hpp
)

# Exe
add_executable(Solitaire ${SOURCES} ${HEADERS})

target_include_directories(Solitaire PRIVATE src/headers)

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Set terminal size for better display
add_custom_command(TARGET Solitaire POST_BUILD
    COMMAND echo "To run the game properly, resize your terminal to at least 70x32 characters"
    COMMAND echo "You can do this with: stty size 32 70"
)
