#ifndef OOP_LAB7_TRIANGLE_H
#define OOP_LAB7_TRIANGLE_H

#include "figure.h"

namespace figures {

    class Triangle : public Figure {
    private:
        Dot *coordinates;
        uint32_t Id_;
    public:
        Triangle();
        explicit Triangle(uint32_t id, std::istream& is);
        Dot Center() const override;
        void PrintOut(std::ostream& os) const override;
        friend std::ostream& operator<<(std::ostream& os, const Triangle& A);
        double Area() const override;
        void Save(std::ofstream& os) const override;
        void Load (std::ifstream& is) override;
        uint32_t Id() const override;
        ~Triangle() override;
    };

} //namespace figures

class Triangle_factory : public Factory {
public:
    std::shared_ptr<figures::Figure> Figure_create() const override;
    std::shared_ptr<figures::Figure> Figure_create(uint32_t id, std::istream& is) const override;
};

#endif //OOP_LAB7_TRIANGLE_H
