#include "terminal.h"

#include <array>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <charconv>

Terminal::Terminal() {
    if (auto [ok, color] = getTerminalBackgroundColor(); ok) {
        alpha_support = true;
        bg_color = color;
    }
    else {
        alpha_support = false;
    }
}

void Terminal::setColor(const ImagePrinter::Color& color, bool is_background = false) {
    if (is_background) {
        std::cout << "\033[48;2;";
    }
    else {
        std::cout << "\033[38;2;";
    }
    std::cout << color.getIntR() << ";" << color.getIntG() << ";" << color.getIntB() << "m";
}

void Terminal::resetColor() {
    std::cout << "\033[0m";
}

void Terminal::printBlock(const ImagePrinter::Color& up_color, const ImagePrinter::Color& down_color) {
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
        if (alpha_support) {
            ImagePrinter::Color tr_up_color = up_color.rgba2rgb(bg_color);
            ImagePrinter::Color tr_down_color = down_color.rgba2rgb(bg_color);
            setColor(tr_up_color);
            setColor(tr_down_color, true);
        }
        else {
            setColor(up_color);
            setColor(down_color, true);
        }
        std::cout << BLOCK_UP;
    }
    resetColor();
}

void Terminal::setCursorPosition(const int row, const int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void Terminal::clearScreen() {
    std::cout << "\033[2J\033[H";
}

std::pair<size_t, size_t> Terminal::getTerminalSize() {
    winsize ws{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return std::make_pair(ws.ws_col, ws.ws_row);
}

std::pair<bool, ImagePrinter::Color> Terminal::getTerminalBackgroundColor() {
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

std::pair<bool, ImagePrinter::Color> Terminal::parseXtermOutput(const std::string& output_) {
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