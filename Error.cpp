#include "Error.hpp"

Error::Error(const char *name) : filename(" ") {
    strcpy(name_of_error, name);
}

Error::Error(const char *name, const char *name1) {
    strcpy(name_of_error, name);
    strcpy(filename, name1);
}

void Error::print_error() const {
    std::cout << "Error : " << name_of_error << "!" << std::endl;
}

const char *Error::get_filename() const {
    return filename;
}

Error_of_insert::Error_of_insert(const char *name) : Error(name) {}

void Error_of_insert::print_error() const {
    std::cout << "Insert Error: " << name_of_error << "!" << std::endl;
}

Error_of_delete::Error_of_delete(const char *name) : Error(name) {}

void Error_of_delete::print_error() const {
    std::cout << "Delete Error: " << name_of_error << "!" << std::endl;
}

Error_of_search::Error_of_search(const char *name) : Error(name) {}

void Error_of_search::print_error() const {
    std::cout << "Search Error: " << name_of_error << "!" << std::endl;
}

File_error::File_error(const char *name, const char *fname) : Error(name, fname) {}

void File_error::print_error() const {
    std::cout << "File Error: " << name_of_error << " !" << std::endl;
}