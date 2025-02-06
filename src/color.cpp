#include "color.h"

Color::Color() : r(0), g(0), b(0) {}

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

