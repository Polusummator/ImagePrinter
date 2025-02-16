#include "printer.h"

#include <argparse/argparse.hpp>

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("./ImagePrinter");

    program.add_argument("image")
        .help("image filename");
    program.add_argument("-b", "--bigger")
        .help("disable vertical adjustment")
        .flag();
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program << std::endl;
        return 1;
    }
    auto filename = program.get("image");
    ImagePrinter::Image image;
    bool status = image.loadImage(filename);
    if (!status) {
        throw std::runtime_error("Failed to load image");
    }
    ImagePrinter::Printer printer(image, !program.get<bool>("-b"));
    printer.print();
    return 0;
}
