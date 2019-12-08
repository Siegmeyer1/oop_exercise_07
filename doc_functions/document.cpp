#include <algorithm>
#include <cstdint>
#include "document.h"

doc_class::Document::Document(): Id_(1), Name_(""), Buf_(0), trg_fact(), sqr_fact(), oct_fact() {}

doc_class::Document::Document(std::string name): Id_(1), Name_(std::move(name)), Buf_(0), trg_fact(), sqr_fact(), oct_fact() {}

void doc_class::Document::Rename(const std::string &new_name) {
    Name_ = new_name;
}

void doc_class::Document::Save(const std::string &filename) const {
    Save_impl(filename);
}

void doc_class::Document::Load(const std::string &filename) {
    Load_impl(filename);
}

void doc_class::Document::Print() const {
    std::for_each(Buf_.begin(), Buf_.end(), [&](const std::shared_ptr<figures::Figure>& shape) {
        shape->PrintOut(std::cout);
        //std::cout << *shape << '\n';
    });
}

void doc_class::Document::Remove_figure(uint32_t id) {
    auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](const std::shared_ptr<figures::Figure>& shape) -> bool {
        return id == shape->Id();
    });

    if (it == Buf_.end())
        throw std::logic_error("Figure with this id doesn't exist");

    Buf_.erase(it);
}

void doc_class::Document::Remove_last_figure() {
    if (Buf_.empty()) {
        throw std::logic_error("Doc is empty");
    }
    Buf_.pop_back();
}

void doc_class::Document::Add_figure(figure_t type, std::istream& is) {
    switch (type) {
        case TRIANGLE:
            Buf_.push_back(trg_fact.Figure_create(Id_++, std::cin));
            break;
        case SQUARE:
            Buf_.push_back(sqr_fact.Figure_create(Id_++, std::cin));
            break;
        case OCTAGON:
            Buf_.push_back(oct_fact.Figure_create(Id_++, std::cin));
            break;
    }
}

uint32_t doc_class::Document::Get_position(uint32_t id) {
    auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](std::shared_ptr<figures::Figure> shape) -> bool {
        return id == shape->Id();
    });
    return std::distance(Buf_.begin(), it);
}

std::shared_ptr<figures::Figure> doc_class::Document::Get_figure(uint32_t id)  { //ПЕРЕДАЧА ПО ССЫЛКЕ
    auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](std::shared_ptr<figures::Figure>& shape) -> bool {
        return id == shape->Id();
    });
    return *it;
}

void doc_class::Document::Insert_figure(uint32_t pos, std::shared_ptr<figures::Figure>& figure) {
    auto it = Buf_.begin();
    std::advance(it, pos);
    Buf_.insert(it, figure);
}

void doc_class::Document::Save_impl(const std::string &filename) const {
    std::ofstream os;
    os.open(filename, std::ios_base::binary | std::ios_base::out);
    if (!os.is_open()) {
        throw std::runtime_error("File is not opened");
    }
    uint32_t format = FORMAT_CODE;
    uint32_t nameLen = Name_.size();
    os.write((char*)&format, sizeof(format));
    os.write((char*)&nameLen, sizeof(nameLen));
    os.write((char*)(Name_.c_str()), nameLen);
    std::for_each(Buf_.begin(), Buf_.end(), [&](const std::shared_ptr<figures::Figure>& shape) {
        shape->Save(os);
    });
}

void doc_class::Document::Load_impl(const std::string &filename) {
    std::ifstream is;
    is.open(filename, std::ios_base::binary | std::ios_base::in);
    if (!is.is_open()) {
        throw std::runtime_error("File is not opened");
    }
    uint32_t format;
    uint32_t nameLen;
    is.read((char*)&format, sizeof(format));
    if (format != FORMAT_CODE)
        throw std::runtime_error("Bad file");
    is.read((char*)&nameLen, sizeof(nameLen));
    char* name = new char[nameLen + 1];
    name[nameLen] = 0;
    is.read(name, nameLen);
    Name_ = std::string(name);
    delete[] name;
    figure_t type;
    while(true) {
        is.read((char*)&type, sizeof(type));
        if (is.eof())
            break;
        switch (type) {
            case TRIANGLE:
                Buf_.push_back(trg_fact.Figure_create());
                break;
            case SQUARE:
                Buf_.push_back(sqr_fact.Figure_create());
                break;
            case OCTAGON:
                Buf_.push_back(oct_fact.Figure_create());
                break;
        }
        Buf_.back()->Load(is);
    }
    Id_ = Buf_.size();
}