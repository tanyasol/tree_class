#ifndef ABSTRACT_TREE_HPP
#define ABSTRACT_TREE_HPP

template <class T>
class ABSTRACT_tree {
public:
    virtual ~ABSTRACT_tree() {}
    virtual void insert(T value) = 0;
    virtual bool delete1(T value) = 0;
    virtual bool search(T value) const = 0;
    virtual void print_tree() const = 0;
    virtual const char *get_tree() const = 0;
};

#endif