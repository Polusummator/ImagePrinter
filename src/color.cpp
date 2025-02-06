#include "color.h"

#include <algorithm>

namespace ImagePrinter {

Color::Color() : r(0), g(0), b(0) {}

Color::Color(int r_, int g_, int b_) : r(r_ / 255.0), g(g_ / 255.0), b(b_ / 255.0) {}

Color::Color(double r_, double g_, double b_): r(r_), g(g_), b(b_) {}

Color Color::operator+(const Color& rhs) const {
    Color result;
    result += *this;
    return result;
}
Color& Color::operator+=(const Color& rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    return *this;
}

Color Color::operator-(const Color& rhs) const {
    Color result;
    result -= *this;
    return result;
}
Color& Color::operator-=(const Color& rhs) {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    return *this;
}

Color Color::operator+(double val) const {
    Color result;
    result += val;
    return result;
}
Color& Color::operator+=(double val) {
    r += val;
    g += val;
    b += val;
    return *this;
}

Color Color::operator-(double val) const {
    Color result;
    result -= val;
    return result;
}
Color& Color::operator-=(double val) {
    r -= val;
    g -= val;
    b -= val;
    return *this;
}

Color Color::operator*(double val) const {
    Color result;
    result *= val;
    return result;
}
Color& Color::operator*=(double val) {
    r *= val;
    g *= val;
    b *= val;
    return *this;
}

Color Color::operator/(double val) const {
    Color result;
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
    return static_cast<int>(std::min(std::max(r, 0.0), 1.0) * 255);
}
int Color::getIntG() const {
    return static_cast<int>(std::min(std::max(g, 0.0), 1.0) * 255);
}
int Color::getIntB() const {
    return static_cast<int>(std::min(std::max(b, 0.0), 1.0) * 255);
}

}
