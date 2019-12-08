#ifndef OOP_LAB7_DOCUMENT_H
#define OOP_LAB7_DOCUMENT_H

#include <fstream>
#include <memory>
#include <list>
#include "../figures/figure.h"
#include "../figures/octagon.h"
#include "../figures/square.h"
#include "../figures/triangle.h"

const uint32_t FORMAT_CODE = 06032001;

namespace doc_class {

    class Document {
    public:
        Document();

        explicit Document(std::string name);

        ~Document() = default;

        void Save(const std::string &filename) const;

        void Load(const std::string &filename);

        void Print() const;

        void Remove_figure(uint32_t id);

        void Remove_last_figure();

        void Add_figure(figure_t type, std::istream &is);

        uint32_t Get_position(uint32_t id);

        std::shared_ptr<figures::Figure> Get_figure(uint32_t id);

        void Insert_figure(uint32_t pos, std::shared_ptr<figures::Figure>& figure);

    private:
        uint32_t Id_;
        std::string Name_;
        std::list<std::shared_ptr<figures::Figure>> Buf_;
        Triangle_factory trg_fact;
        Square_factory sqr_fact;
        Octagon_factory oct_fact;

        void Save_impl(const std::string& filename) const;
        void Load_impl(const std::string& filename);
        };
}

#endif //OOP_LAB7_DOCUMENT_H
