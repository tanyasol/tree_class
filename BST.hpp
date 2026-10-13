#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <cstring>
#include "ABSTRACT_tree.hpp"
#include "Error.hpp"

template <class T>
class BST : public ABSTRACT_tree<T> {
protected:
    struct Tree_node {
        T key;
        Tree_node *left;
        Tree_node *right;
        Tree_node(T val) : key(val), left(nullptr), right(nullptr) {}
        ~Tree_node() {
            if (left) delete left;
            if (right) delete right;
        }
    };

    Tree_node *root;
    int size;
    char tree_type[50];

protected:
    void print_tree1(Tree_node *node) const {
        if (!node) return;
        print_tree1(node->left);
        std::cout << node->key << " ";
        print_tree1(node->right);
    }

    Tree_node *minimum(Tree_node *node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    virtual Tree_node *insert_node(Tree_node *node, T value) {
        if (!node) {
            size++;
            return new Tree_node(value);
        }
        if (value < node->key)
            node->left = insert_node(node->left, value);
        else if (value > node->key)
            node->right = insert_node(node->right, value);
        else
            throw Error_of_insert("Wrong value");
        return node;
    }

    virtual Tree_node *delete_node(Tree_node *node, T value) {
        if (!node) throw Error_of_delete("Value not found");

        if (value < node->key)
            node->left = delete_node(node->left, value);
        else if (value > node->key)
            node->right = delete_node(node->right, value);
        else {
            if (!node->left) {
                Tree_node *tmp = node->right;
                node->right = nullptr;
                delete node;
                return tmp;
            } else if (!node->right) {
                Tree_node *tmp = node->left;
                node->left = nullptr;
                delete node;
                return tmp;
            }
            Tree_node *min_right = minimum(node->right);
            node->key = min_right->key;
            node->right = delete_node(node->right, min_right->key);
            size--;
        }
        return node;
    }

    virtual Tree_node *search_node(Tree_node *node, T value) const {
        if (!node) return node;
        if (node->key == value) return node;
        if (value < node->key)
            return search_node(node->left, value);
        else
            return search_node(node->right, value);
    }

public:
    BST() : root(nullptr), size(0) {
        strcpy(tree_type, "BST");
    }

    BST(const char *type) : root(nullptr), size(0) {
        strcpy(tree_type, type);
    }

    virtual ~BST() {
        if (root) delete root;
    }

    int get_size() const { return size; }
    const char *get_tree() const override { return tree_type; }

    void insert(T value) override {
        try {
            root = insert_node(root, value);
        } catch (const Error &) {
        }
    }

    bool delete1(T value) override {
        try {
            if (!root) throw Error_of_delete("Tree is empty");
            int first_size = size;
            root = delete_node(root, value);
            return first_size > size;
        } catch (const Error &) {
            return false;
        }
    }

    bool search(T value) const override {
        try {
            if (!root) throw Error_of_search("Value does not exists");
            return search_node(root, value) != nullptr;
        } catch (const Error &) {
            return false;
        }
    }

    void print_tree() const override {
        std::cout << get_tree() << ": ";
        print_tree1(root);
        std::cout << std::endl;
    }
};

#endif