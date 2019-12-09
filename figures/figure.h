#ifndef OOP_LAB7_FIGURE_H
#define OOP_LAB7_FIGURE_H

#include <memory>
#include <fstream>
#include <map>
#include "dot.h"

enum figure_t {
    TRIANGLE,
    SQUARE,
    OCTAGON
};

namespace figures {

    class Figure {
    public:
        virtual Dot Center() const = 0;
        virtual void PrintOut(std::ostream& os) const = 0;
        virtual double Area() const = 0;
        virtual void Save(std::ofstream& os) const = 0;
        virtual void Load(std::ifstream& is) = 0;
        virtual uint32_t Id() const = 0;
        virtual ~Figure() = default;
    };

} //namespace figures

class FactoryInterface {
public:
    virtual std::shared_ptr<figures::Figure> Figure_create() const = 0;
    virtual std::shared_ptr<figures::Figure> Figure_create(uint32_t id, std::istream& is) const = 0;
};


#endif //OOP_LAB7_FIGURE_H
