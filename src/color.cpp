#include "color.h"

#include <algorithm>
#include <tuple>

namespace ImagePrinter {

Color::Color() : r(0.0), g(0.0), b(0.0), a(0.0) {}

Color::Color(int r_, int g_, int b_, int a_)
    : r(r_ / RGB_MAX), g(g_ / RGB_MAX), b(b_ / RGB_MAX), a(a_ / RGB_MAX) {}

Color::Color(double r_, double g_, double b_, double a_)
    : r(r_), g(g_), b(b_), a(a_) {}

Color::Color(const Color& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}
Color::Color(Color&& other) noexcept {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

Color& Color::operator=(Color other) {
    std::swap(r, other.r);
    std::swap(g, other.g);
    std::swap(b, other.b);
    std::swap(a, other.a);
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
    a += rhs.a;
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
    a /= val;
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

Color Color::rgba2rgb(const Color& bg_color) const {
    Color result;
    result.r = (1 - a) * bg_color.r + a * r;
    result.g = (1 - a) * bg_color.g + a * g;
    result.b = (1 - a) * bg_color.b + a * b;
    result.a = 1.0;
    return result;
}

}
