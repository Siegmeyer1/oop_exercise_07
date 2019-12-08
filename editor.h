#ifndef OOP_LAB7_EDITOR_H
#define OOP_LAB7_EDITOR_H

#include <stack>
#include "doc_functions/document.h"
#include "command.h"

class Editor {

public:
    Editor(): Doc_(nullptr), History_() {}

    void Create_document(const std::string& name) {
        Doc_ = std::make_shared<doc_class::Document>(name);
    }

    void Insert_figure(figure_t type, std::istream& is) {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new Insert_cmd(type, is));
        command->SetDocument(Doc_);
        command->Execute();
        History_.push(command);
    }

    void Remove_figure(uint32_t id) {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new Remove_cmd(id));
        command->SetDocument(Doc_);
        command->Execute();
        History_.push(command);
    }

    void Save_document(const std::string& filename) {
        Doc_->Save(filename);
    }

    void Load_document(const std::string& filename) {
        Doc_ = std::make_shared<doc_class::Document>("NoName");
        Doc_->Load(filename);
    }

    void Undo() {
        if (History_.empty()) {
            throw std::logic_error("History is empty");
        }
        std::shared_ptr<Command> last_cmd = History_.top();
        last_cmd->Abort();
        History_.pop();
    }

    void Print_document() {
        Doc_->Print();
    }

    bool Document_exist() {
        return Doc_ != nullptr;
    }

    ~Editor() = default;

private:
    std::shared_ptr<doc_class::Document> Doc_;
    std::stack<std::shared_ptr<Command>> History_;
};

#endif //OOP_LAB7_EDITOR_H
