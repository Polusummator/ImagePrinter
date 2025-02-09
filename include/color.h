#pragma once

namespace ImagePrinter {

inline constexpr double RGB_MAX = 255.0;

class Color {
public:
    double r;
    double g;
    double b;

    Color();
    Color(int r_, int g_, int b_);
    Color(double r_, double g_, double b_);
    Color(const Color& other);
    Color(Color&& other) noexcept;

    Color& operator=(Color other);

    Color operator+(const Color& rhs) const;
    Color& operator+=(const Color& rhs);

    Color operator/(double val) const;
    Color& operator/=(double val);

    int getIntR() const;
    int getIntG() const;
    int getIntB() const;
};

}
