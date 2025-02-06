#pragma once

#include "color.h"

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

#define BLOCK "█"
#define BLOCK_UP "▀"
#define BLOCK_DOWN "▄"

inline void setColor(const ImagePrinter::Color& color, const bool is_background = false) {
    if (is_background) {
        std::cout << "\033[48;2;" << color.getIntR() << ";" << color.getIntG() << ";" << color.getIntB() << "m";
    }
    else {
        std::cout << "\033[38;2;" << color.getIntR() << ";" << color.getIntG() << ";" << color.getIntB() << "m";
    }
}

inline void resetColor() {
    std::cout << "\033[0m";
}

inline void printBlock(const ImagePrinter::Color& up_color, const ImagePrinter::Color& down_color) {
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

inline std::pair<size_t, size_t> getTerminalSize() {
    winsize ws{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return std::make_pair(ws.ws_row, ws.ws_col);
}