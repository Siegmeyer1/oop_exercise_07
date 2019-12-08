#include <cmath>
#include "square.h"


namespace figures {

    Square::Square(): Id_(0) {
        coordinates = new Dot[2];
        for (int i = 0; i < 2; ++i) {
            coordinates[i] = "0.0 0.0"_dot;
        }
    }

    Square::Square(uint32_t id, std::istream &is): Id_(id) {
        coordinates = new Dot[2];
        for (size_t i = 0; i < 2; ++i) {
            is >> coordinates[i];
        }
    }

    Dot Square::Center() const {
        Dot res = (this->coordinates[0] + this->coordinates[1]) / 2;
        return res;
    }

    double Square::Area() const{
        double res = this->coordinates[0].Length(this->coordinates[1]);
        res = pow(res , 2) / 2;
        return  res;
    }

    void Square::PrintOut(std::ostream& os) const {
        Dot C = this->Center();
        double tmp;
        Dot res[2];
        for (int i = 0; i < 2; ++i) {
            res[i] = this->coordinates[i];
            res[i] = res[i] - C;
            tmp = res[i].y;
            res[i].y = res[i].x;
            res[i].x = -tmp;
            res[i] = res[i] + C;
        }
        os << "ID: " << Id_ << "\tType: square" << "\t Area: " << Area() << "\t\tCenter: " << Center() << "\t\tDots: ";

        os << res[0] << ", " << this->coordinates[0] << ", "
           << res[1] << ", " << this->coordinates[1] << '\n';
    }

    std::ostream& operator<<(std::ostream& os, const Square& A) {
        Dot C = A.Center();
        double tmp;
        Dot res[2];
        for (int i = 0; i < 2; ++i) {
            res[i] = A.coordinates[i];
            res[i] = res[i] - C;
            tmp = res[i].y;
            res[i].y = res[i].x;
            res[i].x = -tmp;
            res[i] = res[i] + C;
        }
        os << res[0] << ", " << A.coordinates[0] << ", "
           << res[1] << ", " << A.coordinates[1];
        return os;
    }

    uint32_t Square::Id() const {
        return Id_;
    }

    void Square::Save(std::ofstream& os) const {
        figure_t type = SQUARE;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 2; ++i) {
            os << coordinates[i].x << ' ' << coordinates[i].y;
            if (i != 1) os << '\t';
        }
    }

    void Square::Load(std::ifstream& is) {
        is.read((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 2; ++i) {
            is >> coordinates[i].x  >> coordinates[i].y;
        }
    }

    Square::~Square() {
        delete[] coordinates;
    }

} //namespace figures

std::shared_ptr<figures::Figure> Square_factory::Figure_create() const {
    return std::shared_ptr<figures::Figure>(new figures::Square());
}

std::shared_ptr<figures::Figure> Square_factory::Figure_create(uint32_t id, std::istream& is) const {
    return std::shared_ptr<figures::Figure>(new figures::Square(id, is));
}