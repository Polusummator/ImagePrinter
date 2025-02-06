#pragma once

struct Color {
    int r;
    int g;
    int b;

    Color(): r(0), g(0), b(0) {}

    Color(const int r_, const int g_, const int b_): r(r_), g(g_), b(b_) {}
};
