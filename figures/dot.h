#ifndef OOP_LAB7_DOT_H
#define OOP_LAB7_DOT_H

#include <iostream>

namespace figures {

    class Dot {
    public:
        double x;
        double y;
        Dot();
        Dot(double X, double Y);
        Dot& operator=(const Dot &A);
        Dot operator+(const Dot &A);
        Dot operator-(const Dot &A);
        Dot operator/(const double &A);
        friend std::ostream &operator<<(std::ostream &os, const Dot& A);
        friend std::istream &operator>>(std::istream &is, Dot& A);
        double Length(const Dot &A);
    };

    Dot operator""_dot(const char* str, size_t size);

}

#endif //OOP_LAB7_DOT_H
