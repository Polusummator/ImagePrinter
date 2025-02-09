#include "color.h"

#include <algorithm>
#include <tuple>

namespace ImagePrinter {

Color::Color() : r(0), g(0), b(0) {}

Color::Color(int r_, int g_, int b_) : r(r_ / RGB_MAX), g(g_ / RGB_MAX), b(b_ / RGB_MAX) {}

Color::Color(double r_, double g_, double b_): r(r_), g(g_), b(b_) {}

Color::Color(const Color& other) {
    r = other.r;
    g = other.g;
    b = other.b;
}
Color::Color(Color&& other) noexcept {
    r = other.r;
    g = other.g;
    b = other.b;
}

Color& Color::operator=(Color other) {
    std::swap(r, other.r);
    std::swap(g, other.g);
    std::swap(b, other.b);
    return *this;
}

Color Color::operator+(const Color& rhs) const {
    Color result(*this);
    result += rhs;
    return result;
}
Color& Color::operator+=(const Color& rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    return *this;
}

Color Color::operator/(double val) const {
    Color result(*this);
    result /= val;
    return result;
}
Color& Color::operator/=(double val) {
    r /= val;
    g /= val;
    b /= val;
    return *this;
}

int Color::getIntR() const {
    return static_cast<int>(std::clamp(r, 0.0, 1.0) * RGB_MAX);
}
int Color::getIntG() const {
    return static_cast<int>(std::clamp(g, 0.0, 1.0) * RGB_MAX);
}
int Color::getIntB() const {
    return static_cast<int>(std::clamp(b, 0.0, 1.0) * RGB_MAX);
}

}
