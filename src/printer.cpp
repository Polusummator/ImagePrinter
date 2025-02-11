#include "printer.h"

#include <iostream>

namespace ImagePrinter {

Printer::Printer(const Image& image) : image(image) {
    auto [terminal_width, terminal_height] = term.getTerminalSize();
    block_size = (image.getWidth() + terminal_width - 1) / terminal_width;
    cnt_blocks_width = (image.getWidth() + block_size - 1) / block_size;
    cnt_blocks_height = (image.getHeight() + block_size - 1) / block_size;
    result_pixels.resize(cnt_blocks_height, std::vector<Color>(cnt_blocks_width));
}

void Printer::print() {
    for (size_t x = 0; x < cnt_blocks_height; ++x) {
        for (size_t y = 0; y < cnt_blocks_width; ++y) {
            result_pixels[x][y] = getMeanColor(x * block_size, y * block_size);
        }
    }

    for (size_t x = 0; x < cnt_blocks_height; x += 2) {
        for (size_t y = 0; y < cnt_blocks_width; ++y) {
            if (x + 1 < cnt_blocks_height) {
                term.printBlock(result_pixels[x][y], result_pixels[x + 1][y]);
            }
            else {
                term.printBlock(result_pixels[x][y], {});
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Color Printer::getMeanColor(size_t x, size_t y) const {
    Color result;
    double cnt = 0.0;
    for (size_t i = x; i < std::min(x + block_size, image.getHeight()); ++i) {
        for (size_t j = y; j < std::min(y + block_size, image.getWidth()); ++j) {
            result += image.getPixel(i, j);
            cnt += 1.0;
        }
    }
    result /= cnt;
    return result;
}

}