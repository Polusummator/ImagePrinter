#pragma once

#include "color.h"

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <charconv>

inline constexpr auto EMPTY_BLOCK = " ";
inline constexpr auto BLOCK = "█";
inline constexpr auto BLOCK_UP = "▀";
inline constexpr auto BLOCK_DOWN = "▄";
static constexpr double BG_MAX = 65535.0;


inline void setColor(const ImagePrinter::Color& color, const bool is_background = false) {
    if (is_background) {
        std::cout << "\033[48;2;";
    }
    else {
        std::cout << "\033[38;2;";
    }
    std::cout << color.getIntR() << ";" << color.getIntG() << ";" << color.getIntB() << "m";
}

inline void resetColor() {
    std::cout << "\033[0m";
}

inline void printBlock(const ImagePrinter::Color& up_color, const ImagePrinter::Color& down_color) {
    if (up_color.a == 0.0) {
        resetColor();
        if (down_color.a == 0.0) {
            std::cout << EMPTY_BLOCK;
        }
        else {
            setColor(down_color);
            std::cout << BLOCK_DOWN;
        }
    }
    else if (down_color.a == 0.0) {
        resetColor();
        setColor(up_color);
        std::cout << BLOCK_UP;

    }
    else {
        setColor(up_color);
        setColor(down_color, true);
        std::cout << BLOCK_UP;
    }
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
    return std::make_pair(ws.ws_col, ws.ws_row);
}

static std::pair<bool, ImagePrinter::Color> parseXtermOutput(const std::string& output_) {
    std::string output = output_ + '/';
    size_t n = output.size();
    if (n == 0) {
        return std::make_pair(false, ImagePrinter::Color());
    }
    size_t pos_colon = output.find_first_of(':');
    if (pos_colon == std::string::npos) {
        return std::make_pair(false, ImagePrinter::Color());
    }
    int cnt = 0;
    std::array<int, 3> colors{};
    std::string current;
    for (size_t i = pos_colon + 1; i < n; ++i) {
        if (output[i] == '/') {
            int color;
            auto [ptr, ec] = std::from_chars(current.data(), current.data() + current.size(), color, 16);
            if (ec != std::errc()) {
                return std::make_pair(false, ImagePrinter::Color());
            }
            colors[cnt] = color;
            cnt++;
            if (cnt > 3) {
                return std::make_pair(false, ImagePrinter::Color());
            }
            current.clear();
        }
        else {
            current += output[i];
        }
    }
    if (cnt < 3) {
        return std::make_pair(false, ImagePrinter::Color());
    }
    ImagePrinter::Color result(colors[0] / BG_MAX, colors[1] / BG_MAX, colors[2] / BG_MAX, 1.0);
    return std::make_pair(true, result);
}


inline std::pair<bool, ImagePrinter::Color> getTerminalBackgroundColor() {
    std::array<char, 128> buffer{};
    std::string result;

    auto pipe = popen("xtermcontrol --get-bg", "r");
    if (!pipe) {
        return std::make_pair(false, ImagePrinter::Color());
    }

    while (!feof(pipe)) {
        if (fgets(buffer.data(),  buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
    }
    auto ret_code = pclose(pipe);
    if (ret_code != EXIT_SUCCESS) {
        return std::make_pair(false, ImagePrinter::Color());
    }
    result.pop_back();
    return parseXtermOutput(result);
}

