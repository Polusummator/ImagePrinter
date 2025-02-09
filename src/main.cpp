#include "printer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("No filename given");
    }
    ImagePrinter::Image image;
    bool status = image.loadImage(argv[1]);
    if (!status) {
        throw std::runtime_error("Failed to load image");
    }
    ImagePrinter::Printer printer(image);
    printer.print();
    return 0;
}
