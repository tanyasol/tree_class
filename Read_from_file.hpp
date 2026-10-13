#ifndef READ_FROM_FILE_HPP
#define READ_FROM_FILE_HPP

#include <fstream>
#include <cstring>
#include "BST.hpp"
#include "AVL.hpp"
#include "Error.hpp"

template <class T>
class Read_from_file {
private:
    char filename[100];

public:
    Read_from_file() {
        filename[0] = '\0';
    }

    Read_from_file(const char *fname) {
        strcpy(filename, fname);
    }

    void set_filename(const char *fname) {
        strcpy(filename, fname);
    }

    void read_to_tree(BST<T> *tree) {
        if (filename[0] == '\0')
            throw File_error("No filename", " ");

        std::ifstream file(filename);
        if (!file) {
            char error_name[50];
            strcpy(error_name, "Cannot open file ");
            strcat(error_name, filename);
            throw File_error(error_name, filename);
        }

        T value;
        while (file >> value) {
            try {
                tree->insert(value);
            } catch (const Error &) {
            }
        }
        file.close();
    }

    void read_to_tree1(AVL<T> *tree) {
        if (filename[0] == '\0')
            throw File_error("No filename", " ");

        std::ifstream file(filename);
        if (!file) {
            char error_name[50];
            strcpy(error_name, "Cannot open file ");
            strcat(error_name, filename);
            throw File_error(error_name, filename);
        }

        T value;
        while (file >> value) {
            try {
                tree->insert(value);
            } catch (const Error &) {
            }
        }
        file.close();
    }
};

#endif