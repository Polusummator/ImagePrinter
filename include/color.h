#pragma once

namespace ImagePrinter {

struct Color {
    double r;
    double g;
    double b;

    Color();
    Color(int r_, int g_, int b_);
    Color(double r_, double g_, double b_);

    Color operator+(const Color& rhs) const;
    Color& operator+=(const Color& rhs);

    Color operator-(const Color& rhs) const;
    Color& operator-=(const Color& rhs);

    Color operator+(double val) const;
    Color& operator+=(double val);

    Color operator-(double val) const;
    Color& operator-=(double val);

    Color operator*(double val) const;
    Color& operator*=(double val);

    Color operator/(double val) const;
    Color& operator/=(double val);

    int getIntR() const;
    int getIntG() const;
    int getIntB() const;
};

}
