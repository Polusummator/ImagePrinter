#pragma once

#include "color.h"

#include <string>

inline constexpr auto EMPTY_BLOCK = " ";
inline constexpr auto BLOCK = "█";
inline constexpr auto BLOCK_UP = "▀";
inline constexpr auto BLOCK_DOWN = "▄";
static constexpr double BG_MAX = 65535.0;

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
};
