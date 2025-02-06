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

    Color getPixel(int x, int y) const;

    size_t getWidth() const;

    size_t getHeight() const;
private:
    Magick::Image image;
};

}