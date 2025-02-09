#pragma once

#include "image.h"
#include "terminal.h"

namespace ImagePrinter {

class Printer {
public:
    explicit Printer(const Image& image);

    void print();
private:
    Image image;
    size_t block_size;
    size_t cnt_blocks_width;
    size_t cnt_blocks_height;
    std::vector<std::vector<Color>> result_pixels;

    Color getMeanColor(size_t x, size_t y) const;
};

}