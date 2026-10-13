#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <cstring>
#include "ABSTRACT_tree.hpp"
#include "Error.hpp"

template <class T>
class AVL : public ABSTRACT_tree<T> {
protected:
    struct Tree_node_AVL {
        T key;
        Tree_node_AVL *left;
        Tree_node_AVL *right;
        int h;
        Tree_node_AVL(T val) : key(val), left(nullptr), right(nullptr), h(1) {}
        ~Tree_node_AVL() {
            if (left) delete left;
            if (right) delete right;
        }
    };

    Tree_node_AVL *root;
    int size;
    char tree_type[50];

private:
    void print_tree1(Tree_node_AVL *node) const {
        if (!node) return;
        print_tree1(node->left);
        std::cout << node->key << " ";
        print_tree1(node->right);
    }

    Tree_node_AVL *minimum(Tree_node_AVL *node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    int h_difference(Tree_node_AVL *node) const {
        if (!node) return 0;
        int l_h = node->left ? node->left->h : 0;
        int r_h = node->right ? node->right->h : 0;
        return l_h - r_h;
    }

    void h_change(Tree_node_AVL *node) {
        if (!node) return;
        int l_h = node->left ? node->left->h : 0;
        int r_h = node->right ? node->right->h : 0;
        node->h = (l_h > r_h ? l_h : r_h) + 1;
    }

    Tree_node_AVL *rotate_right(Tree_node_AVL *t) {
        Tree_node_AVL *a = t->left;
        Tree_node_AVL *b = a->right;
        a->right = t;
        t->left = b;
        h_change(t);
        h_change(a);
        return a;
    }

    Tree_node_AVL *rotate_left(Tree_node_AVL *t) {
        Tree_node_AVL *a = t->right;
        Tree_node_AVL *b = a->left;
        a->left = t;
        t->right = b;
        h_change(t);
        h_change(a);
        return a;
    }

    Tree_node_AVL *balance(Tree_node_AVL *node) {
        if (!node) return node;
        h_change(node);
        int hdif = h_difference(node);

        if (hdif > 1 && h_difference(node->left) >= 0)
            return rotate_right(node);
        if (hdif < -1 && h_difference(node->right) <= 0)
            return rotate_left(node);
        if (hdif > 1 && h_difference(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (hdif < -1 && h_difference(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    Tree_node_AVL *insert_node1(Tree_node_AVL *node, T value) {
        if (!node) {
            size++;
            return new Tree_node_AVL(value);
        }
        if (value < node->key)
            node->left = insert_node1(node->left, value);
        else if (value > node->key)
            node->right = insert_node1(node->right, value);
        else
            throw Error_of_insert("Value already exists");
        return balance(node);
    }

    Tree_node_AVL *delete_node1(Tree_node_AVL *node, T value) {
        if (!node) throw Error_of_delete("Value not found");

        if (value < node->key)
            node->left = delete_node1(node->left, value);
        else if (value > node->key)
            node->right = delete_node1(node->right, value);
        else {
            if (!node->left || !node->right) {
                Tree_node_AVL *tmp = node->left ? node->left : node->right;
                if (!tmp) {
                    delete node;
                    return nullptr;
                } else {
                    node->left = nullptr;
                    node->right = nullptr;
                    delete node;
                    return tmp;
                }
            } else {
                Tree_node_AVL *min_right = minimum(node->right);
                node->key = min_right->key;
                node->right = delete_node1(node->right, min_right->key);
            }
            size--;
        }
        if (!node) return node;
        return balance(node);
    }

    Tree_node_AVL *search_node1(Tree_node_AVL *node, T value) const {
        if (!node) return node;
        if (node->key == value) return node;
        if (value < node->key)
            return search_node1(node->left, value);
        else
            return search_node1(node->right, value);
    }

public:
    AVL() : root(nullptr), size(0) {
        strcpy(tree_type, "AVL");
    }

    ~AVL() {
        if (root) delete root;
    }

    const char *get_tree() const override { return tree_type; }

    void print_tree() const override {
        std::cout << get_tree() << ": ";
        print_tree1(root);
        std::cout << std::endl;
    }

    void insert(T value) override {
        try {
            root = insert_node1(root, value);
        } catch (const Error &) {
        }
    }

    bool delete1(T value) override {
        try {
            if (!root) throw Error_of_delete("Tree is empty");
            int old_size = size;
            root = delete_node1(root, value);
            return old_size > size;
        } catch (const Error &) {
            return false;
        }
    }

    bool search(T value) const override {
        try {
            if (!root) throw Error_of_search("Value does not exists");
            return search_node1(root, value) != nullptr;
        } catch (const Error &) {
            return false;
        }
    }
};

#endif