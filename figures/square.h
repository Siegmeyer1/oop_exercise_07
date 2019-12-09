#ifndef OOP_LAB7_SQUARE_H
#define OOP_LAB7_SQUARE_H

#include "figure.h"

namespace figures {

    class Square : public Figure {
    private:
        Dot *coordinates;
        uint32_t Id_;
    public:
        Square();
        explicit Square(uint32_t id, std::istream& is);
        Dot Center() const override;
        double Area() const override ;
        void PrintOut(std::ostream& os) const override;
        uint32_t Id() const override;
        void Save(std::ofstream& os) const override;
        void Load(std::ifstream& is) override;
        friend std::ostream& operator<<(std::ostream& os, const Square& A);
        ~Square() override;
    };

} //namespace figures

class Square_factory : public FactoryInterface {
public:
    std::shared_ptr<figures::Figure> Figure_create() const override;
    std::shared_ptr<figures::Figure> Figure_create(uint32_t id, std::istream& is) const override;
};

#endif //OOP_LAB7_SQUARE_H
