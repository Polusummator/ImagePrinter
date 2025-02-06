#pragma once

#include "color.h"

#include <iostream>

#define BLOCK "█"
#define BLOCK_UP "▀"
#define BLOCK_DOWN "▄"

inline void setColor(const Color& color, const bool is_background = false) {
    if (is_background) {
        std::cout << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";
    }
    else {
        std::cout << "\033[38;2;" << color.r << ";" << color.g << ";" << color.b << "m";
    }
}

inline void resetColor() {
    std::cout << "\033[0m";
}

inline void printBlock(const Color& up_color, const Color& down_color) {
    setColor(up_color);
    setColor(down_color, true);
    std::cout << BLOCK_UP;
    resetColor();
}

inline void setCursorPosition(const int row, const int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

inline void clearScreen() {
    std::cout << "\033[2J\033[H";
}