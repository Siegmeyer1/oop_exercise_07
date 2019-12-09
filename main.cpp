#include <iostream>
#include "editor.h"

bool quit (Editor& editor) {
    char c;
    std::cout << "Do you want to save before exit? [Y/N]: ";
    std::cin >> c;
    if (c == 'N' || c == 'n') {
        return true;
    }
    else if (c == 'Y' || c == 'y') {
        std::string name;
        std::cout << "Enter name for savefile: ";
        std::cin >> name;
        try {
            editor.Save_document(name);
            std::cout << "Successfully saved in " << name << '\n';
        } catch  (std::runtime_error& err) {
            std::cout << err.what() << "\n";
            return false;
        }
        return true;
    } else {
        std::cout << "so yes or no?\n";
        return false;
    }
}

void man () {
    std::cout << "create - create new document\n"
    << "save - save current document to file\n"
    << "load - load document from file\n"
    << "add - add new figure\n"
    << "remove - remove figure by it`s ID\n"
    << "undo - abort previous operation\n"
    << "print - print the document contents\n"
    << "quit - close program and exit\n";
}

bool create(Editor& editor) {
    char c;
    if (editor.Document_exist()) {
        std::cout << "Save current document? [Y/N]\n";
        std::cin >> c;
        if (c == 'N' || c == 'n') {
        }
        else if (c == 'Y' || c == 'y') {
            std::string name;
            std::cout << "Enter name for savefile: ";
            std::cin >> name;
            try {
                editor.Save_document(name);
                std::cout << "Successfully saved in " << name << '\n';
            } catch  (std::runtime_error& err) {
                std::cout << err.what() << "\n";
                return false;
            }
        } else {
            std::cout << "so yes or no?\n";
            return false;
        }
    }
    std::string doc_name;
    std::cout << "Enter name of new project\n";
    std::cin >> doc_name;
    editor.Create_document(doc_name);
    std::cout << "Document " << doc_name << " is created\n";
    return true;
}

bool load(Editor& editor) {
    char c;
    if (editor.Document_exist()) {
        std::cout << "Save current document? [Y/N]\n";
        std::cin >> c;
        if (c == 'N' || c == 'n') {
        }
        else if (c == 'Y' || c == 'y') {
            std::string name;
            std::cout << "Enter name for savefile: ";
            std::cin >> name;
            try {
                editor.Save_document(name);
                std::cout << "Successfully saved in " << name << '\n';
            } catch  (std::runtime_error& err) {
                std::cout << err.what() << "\n";
                return false;
            }
        } else {
            std::cout << "so yes or no?\n";
            return false;
        }
    }
    std::string file_name;
    std::cout << "Enter name of load file\n";
    std::cin >> file_name;
    try {
        editor.Load_document(file_name);
        std::cout << "Successfully loaded from " << file_name << "\n";
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
        return false;
    }
    return true;
}

bool save(Editor& editor) {
    std::string file_name;
    std::cout << "Enter name for savefile: ";
    std::cin >> file_name;

    try {
        editor.Save_document(file_name);
        std::cout << "Successfully saved in " << file_name << '\n';
    } catch (std::runtime_error& err) {
        std::cout << err.what() << "\n";
        return false;
    }
    return true;
}

void add (Editor& editor) {
    /*int type;
    std::cout << "Enter type of figure (1 for triangle, 2 for square, 3 - for octagon): ";
    std::cin >> type;
    switch(type) {
        case 1:
            std::cout << "Enter triangle (X, then Y for each dot): ";
            editor.Insert_figure(TRIANGLE, std::cin);
            break;
        case 2:
            std::cout << "Enter square (coordinates of 2 opposite angles): ";
            editor.Insert_figure(SQUARE, std::cin);
            break;
        case 3:
            std::cout << "Enter octagon (enter dots consequently): ";
            editor.Insert_figure(OCTAGON, std::cin);
            break;
        default:
            std::cout << "Please, enter 1, 2 or 3 to choose figure\n";
            return;
    }*/
    std::string name;
    std::cin >> name;
    editor.Insert_figure(editor.Doc_->factory.figure_names[name], std::cin);
    std::cout << "Figure is added\n";
}

bool remove(Editor& editor) {
    uint32_t id;
    std::cout << "enter ID of figure you fant to remove (you can see it in print): ";
    std::cin >> id;

    try {
        editor.Remove_figure(id);
        std::cout << "Figure with ID " << id << " is removed\n";
    } catch (std::logic_error& err) {
        std::cout << err.what() << "\n";
        return false;
    }
    return true;
}



int main() {
    Editor editor;
    std::string cmd;

    while (cmd != "quit") {
        std::cin >> cmd;
        if (cmd == "quit") {
           if (quit(editor))
           {
               return 0;
           }
        } else if (cmd == "man") {
            man();
        } else if (cmd == "create") {
            create(editor);
        } else if (cmd == "save") {
            save(editor);
        } else if (cmd == "load") {
            load(editor);
        } else if (cmd == "add") {
            add(editor);
        } else if (cmd == "remove") {
            remove(editor);
        } else if (cmd == "undo") {
            editor.Undo();
            std::cout << "Done (hopefully)\n";
        } else if (cmd == "print") {
            editor.Print_document();
        }
    }
    return 0;
}