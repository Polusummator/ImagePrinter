#include "image.h"

#include <iostream>

namespace ImagePrinter {

Image::Image() {
    Magick::InitializeMagick(nullptr);
}

Image::~Image() = default;

bool Image::loadImage(const std::string& filename) {
    try {
        image.read(filename);
    }
    catch (Magick::Exception& error) {
        std::cerr << error.what() << std::endl;
        return false;
    }
    return true;
}

Color Image::getPixel(int x, int y) const {
    Magick::ColorRGB pixel = image.pixelColor(x, y);
    return {pixel.red(), pixel.green(), pixel.blue()};
}

size_t Image::getWidth() const {
    return image.columns();
}

size_t Image::getHeight() const {
    return image.rows();
}

}






