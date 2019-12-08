#include "triangle.h"

namespace figures {

    Triangle::Triangle(): Id_(0) {
        coordinates = new Dot[3];
        for (int i = 0; i < 3; ++i) {
            coordinates[i] = "0.0 0.0"_dot;
        }
    }

    Triangle::Triangle(uint32_t id, std::istream &is): Id_(id) {
        coordinates = new Dot[3];
        for (size_t i = 0; i < 3; ++i) {
            is >> coordinates[i];
        }
    }

    Dot Triangle::Center() const {
        Dot res(0, 0);
        for (int i = 0; i < 3; ++i) {
            res = res + coordinates[i];
        }
        res = res / 3.0;
        return res;
    }

    double Triangle::Area() const {
        double x1 = this->coordinates[0].x;
        double x2 = this->coordinates[1].x;
        double x3 = this->coordinates[2].x;
        double y1 = this->coordinates[0].y;
        double y2 = this->coordinates[1].y;
        double y3 = this->coordinates[2].y;

        double res = std::abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)) / 2;
        return res;
    }

    void Triangle::PrintOut(std::ostream& os) const {
        os << "ID: " << Id_ << "\tType: triangle" << "\t Area: " << Area() << "\t\tCenter: " << Center() << "\t\tDots: ";
        for (int i = 0; i < 3; ++i) {
            os  << coordinates[i];
            if (i != 2) {
                os << ", ";
            }
        }
        os << '\n';
    }

    void Triangle::Save(std::ofstream& os) const {
        figure_t type = TRIANGLE;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 3; ++i) {
            os << coordinates[i].x << ' ' << coordinates[i].y;
            if (i != 2) os << '\t';
        }
    }

    void Triangle::Load(std::ifstream &is) {
        is.read((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 3; ++i) {
            is >> coordinates[i].x  >> coordinates[i].y;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Triangle& A) {
        for (int i = 0; i < 3; ++i) {
            os << A.coordinates[i];
            if (i != 2) {
                os << ", ";
            }
        }
        return os;
    }

    uint32_t Triangle::Id() const {
        return Id_;
    }


    Triangle::~Triangle() {
        delete[] coordinates;
    }

}//namespace figures

std::shared_ptr<figures::Figure> Triangle_factory::Figure_create() const {
    return std::shared_ptr<figures::Figure>(new figures::Triangle());
}

std::shared_ptr<figures::Figure> Triangle_factory::Figure_create(uint32_t id, std::istream& is) const {
    return std::shared_ptr<figures::Figure>(new figures::Triangle(id, is));
}