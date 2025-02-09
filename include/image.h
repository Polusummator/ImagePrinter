#pragma once

#include "color.h"

#include <Magick++.h>

#include <string>

namespace ImagePrinter {

class Image {
public:
    Image();

    ~Image();

    bool loadImage(const std::string& filename);

    Color getPixel(size_t x, size_t y) const;

    size_t getWidth() const;

    size_t getHeight() const;
private:
    Magick::Image image;
};

}