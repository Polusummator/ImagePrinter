#pragma once

#include "color.h"

#include <string>

class Terminal {
public:
    Terminal();

    void setColor(const ImagePrinter::Color& color, bool is_background);

    void resetColor();

    void printBlock(const ImagePrinter::Color& up_color, const ImagePrinter::Color& down_color);

    void setCursorPosition(int row, int col);

    void clearScreen();

    std::pair<size_t, size_t> getTerminalSize();

    std::pair<bool, ImagePrinter::Color> getTerminalBackgroundColor();

private:
    std::pair<bool, ImagePrinter::Color> parseXtermOutput(const std::string& output_);

    static constexpr auto EMPTY_BLOCK = " ";
    static constexpr auto BLOCK = "█";
    static constexpr auto BLOCK_UP = "▀";
    static constexpr auto BLOCK_DOWN = "▄";
    static constexpr double BG_MAX = 65535.0;
};
