#include "octagon.h"

namespace figures {

    double Octagon::Area() const {
        double res = 0;
        for (size_t i = 0; i < 7; i++) {
            res += (coordinates[i].x * coordinates[i+1].y) - (coordinates[i+1].x * coordinates[i].y);
        }
        res = res + (coordinates[7].x * coordinates[0].y) - (coordinates[0].x * coordinates[7].y);
        return std::abs(res)/ 2;
    }

    Dot Octagon::Center() const {
        Dot res(0, 0);
        for (int i = 0; i < 8; ++i) {
            res = res + coordinates[i];
        }
        res = res / 8.0;
        return res;
    }

    void Octagon::PrintOut(std::ostream& os) const {
        os << "ID: " << Id_ << "\tType: octagon" << "\t Area: " << Area() << "\t\tCenter: " << Center() << "\t\tDots: ";
        for (int i = 0; i < 8; ++i) {
            os << this->coordinates[i];
            if (i != 7) {
                os << ", ";
            }
        }
        os << '\n';
    }

    std::ostream& operator<<(std::ostream& os, const Octagon& A) {
        for (int i = 0; i < 8; ++i) {
            os << A.coordinates[i];
            if (i != 7) {
                os << ", ";
            }
        }
        return os;
    }

    Octagon::Octagon(): Id_(0) {
        coordinates = new Dot[8];
        for (int i = 0; i < 8; ++i) {
            coordinates[i] = "0.0 0.0"_dot;
        }
    }

    Octagon::Octagon(uint32_t id, std::istream &is): Id_(id) {
        coordinates = new Dot[8];
        for (size_t i = 0; i < 8; ++i) {
            is >> coordinates[i];
        }
    }

    uint32_t Octagon::Id() const {
        return Id_;
    }

    void Octagon::Save(std::ofstream& os) const {
        figure_t type = OCTAGON;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 8; ++i) {
            os << coordinates[i].x << ' ' << coordinates[i].y;
            if (i != 7) os << '\t';
        }
    }

    void Octagon::Load(std::ifstream& is) {
        is.read((char*)(&Id_), sizeof(Id_));
        for (int i = 0; i < 8; ++i) {
            is >> coordinates[i].x  >> coordinates[i].y;
        }
    }

    Octagon::~Octagon() {
        delete[] this->coordinates;
    }

} //namespace figures

std::shared_ptr<figures::Figure> Octagon_factory::Figure_create() const {
    return std::shared_ptr<figures::Figure>(new figures::Octagon());
}

std::shared_ptr<figures::Figure> Octagon_factory::Figure_create(uint32_t id, std::istream& is) const {
    return std::shared_ptr<figures::Figure>(new figures::Octagon(id, is));
}