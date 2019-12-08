#include <sstream>
#include <cmath>
#include "dot.h"

namespace figures {

    Dot::Dot() {
        x = 0;
        y = 0;
    }

    Dot::Dot(double X, double Y) {
        x = X;
        y = Y;
    }

    Dot operator""_dot(const char* str, size_t size) {
        std::istringstream is(str);
        char tmp;
        double x, y;
        is >> x >> tmp >> y;
        return {x, y};
    }

    Dot& Dot::operator=(const Dot &A) {
        this->x = A.x;
        this->y = A.y;
        return *this;
    }

    Dot Dot::operator+(const Dot &A) {
        Dot res;
        res.x = this->x + A.x;
        res.y = this->y + A.y;
        return res;
    }

    Dot Dot::operator-(const Dot &A) {
        Dot res;
        res.x = this->x - A.x;
        res.y = this->y - A.y;
        return res;
    }

    Dot Dot::operator/(const double &A) {
        Dot res;
        res.x = this->x / A;
        res.y = this->y / A;
        return res;
    }

    std::ostream &operator<<(std::ostream &os, const Dot& A) {
        os << "(" << A.x << "; " << A.y << ")";
        return os;
    }

    std::istream &operator>>(std::istream &is, Dot& A) {
        is >> A.x >> A.y;
        return is;
    }

    double Dot::Length(const Dot &A) {
        double res;
        res = sqrt(pow(this->x - A.x, 2) + pow(this->y - A.y, 2));
        return res;
    }

} // namespace figures