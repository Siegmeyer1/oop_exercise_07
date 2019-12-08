#ifndef OOP_LAB7_COMMAND_H
#define OOP_LAB7_COMMAND_H

#include <stack>
#include <utility>
#include "doc_functions/document.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void Abort() = 0;
    void SetDocument(std::shared_ptr<doc_class::Document> doc) {
        Doc_ = std::move(doc); //МУВ ДЛЯ ИЗБЕГАНИЯ ЛИШНЕГО КОПИРОВАНИЯ
    }
protected:
    std::shared_ptr<doc_class::Document> Doc_;
};

class Insert_cmd: public Command {
public:
    Insert_cmd(figure_t type, std::istream& is): Type_(type), Input_stream_(is) {}

    void Execute() override {
        Doc_->Add_figure(Type_, Input_stream_);
    }
    void Abort() override {
        Doc_->Remove_last_figure();
    }

private:
    figure_t Type_;
    std::istream& Input_stream_;
};

class Remove_cmd : public Command {
public:
    explicit Remove_cmd(uint32_t id): Id_(id), Pos_(0), Figure_(nullptr) {}

    void Execute() override {
        Figure_ = Doc_->Get_figure(Id_);
        Pos_ = Doc_->Get_position(Id_);
        Doc_->Remove_figure(Id_);
    }

    void Abort() override {
        Doc_->Insert_figure(Pos_, Figure_);
    }

private:
    uint32_t Id_;
    uint32_t Pos_;
    std::shared_ptr<figures::Figure> Figure_;

};

#endif //OOP_LAB7_COMMAND_H
