#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <cstring>

class Error {
protected:
    char name_of_error[50];
    char filename[100];
public:
    Error(const char *name);
    Error(const char *name, const char *name1);
    virtual ~Error() = default;

    virtual void print_error() const;
    const char *get_filename() const;
};

class Error_of_insert : public Error {
public:
    Error_of_insert(const char *name);
    void print_error() const override;
};

class Error_of_delete : public Error {
public:
    Error_of_delete(const char *name);
    void print_error() const override;
};

class Error_of_search : public Error {
public:
    Error_of_search(const char *name);
    void print_error() const override;
};

class File_error : public Error {
public:
    File_error(const char *name, const char *fname);
    void print_error() const override;
};

#endif