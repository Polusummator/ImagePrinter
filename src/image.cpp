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
    image.colorSpace(Magick::scRGBColorspace);
    image.colorSpace(Magick::sRGBColorspace);
    return true;
}

Color Image::getPixel(size_t x, size_t y) const {
#if IMAGEMAGICK_VERSION == 6
    Magick::Color pixel = image.pixelColor(y, x);
    using Magick::Quantum;
    return {static_cast<double>(pixel.redQuantum()) / QuantumRange,
            static_cast<double>(pixel.greenQuantum()) / QuantumRange,
            static_cast<double>(pixel.blueQuantum()) / QuantumRange,
            1 - pixel.alpha()
    };
#else
    Magick::ColorRGB pixel = image.pixelColor(y, x);
    return {pixel.red(), pixel.green(), pixel.blue(), pixel.alpha()};
#endif
}

size_t Image::getWidth() const {
    return image.columns();
}

size_t Image::getHeight() const {
    return image.rows();
}

}






