#ifndef OOP_LAB7_OCTAGON_H
#define OOP_LAB7_OCTAGON_H

#include "figure.h"

namespace figures {

    class Octagon : public Figure {
    private:
        Dot* coordinates;
        uint32_t Id_;
    public:
        Octagon();
        explicit Octagon(uint32_t id, std::istream& is);
        Dot Center() const override;
        void PrintOut(std::ostream& os) const override;
        friend std::ostream& operator<<(std::ostream& os, const Octagon& A);
        uint32_t Id() const override;
        double Area() const override;
        void Save(std::ofstream& os) const override;
        void Load(std::ifstream& is) override;
        ~Octagon() override;
    };

} //namespace figures

class Octagon_factory : public FactoryInterface {
public:
    std::shared_ptr<figures::Figure> Figure_create() const override;
    std::shared_ptr<figures::Figure> Figure_create(uint32_t id, std::istream& is) const override;
};

#endif //OOP_LAB7_OCTAGON_H
