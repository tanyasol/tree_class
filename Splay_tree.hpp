#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include "BST.hpp"
#include "Error.hpp"

template <class T>
class Splay_tree : public BST<T> {
protected:
    using BST<T>::root;
    using BST<T>::size;
    using typename BST<T>::Tree_node;

private:
    Tree_node *rotate_right(Tree_node *x) {
        Tree_node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Tree_node *rotate_left(Tree_node *x) {
        Tree_node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Tree_node *splay(Tree_node *node, T value) {
        if (!node || node->key == value) return node;

        if (value < node->key) {
            if (!node->left) return node;

            if (value < node->left->key) {
                node->left->left = splay(node->left->left, value);
                node = rotate_right(node);
            } else if (value > node->left->key) {
                node->left->right = splay(node->left->right, value);
                if (node->left->right)
                    node->left = rotate_left(node->left);
            }
            return (node->left) ? rotate_right(node) : node;
        } else {
            if (!node->right) return node;

            if (value < node->right->key) {
                node->right->left = splay(node->right->left, value);
                if (node->right->left)
                    node->right = rotate_right(node->right);
            } else if (value > node->right->key) {
                node->right->right = splay(node->right->right, value);
                node = rotate_left(node);
            }
            return (node->right) ? rotate_left(node) : node;
        }
    }

public:
    Splay_tree() : BST<T>("Splay Tree") {}

    void insert(T value) override {
        try {
            if (!root) {
                root = new Tree_node(value);
                size++;
                return;
            }
            root = splay(root, value);
            if (root->key == value)
                throw Error_of_insert("Value cannot be insert");

            Tree_node *new_node = new Tree_node(value);
            size++;
            if (value < root->key) {
                new_node->right = root;
                new_node->left = root->left;
                root->left = nullptr;
            } else {
                new_node->left = root;
                new_node->right = root->right;
                root->right = nullptr;
            }
            root = new_node;
        } catch (const Error &) {
        }
    }

    bool delete1(T value) override {
        try {
            if (!root) throw Error_of_delete("Tree is empty");

            root = splay(root, value);
            if (root->key != value)
                throw Error_of_delete("Value not found");

            Tree_node *tmp = root;

            if (!root->left) {
                root = root->right;
            } else {
                Tree_node *l_tree = root->left;
                Tree_node *mx = l_tree;
                while (mx->right) mx = mx->right;

                Tree_node *root1 = splay(l_tree, mx->key);
                if (root1) {
                    root1->right = root->right;
                    root = root1;
                }
            }

            if (tmp) {
                tmp->left = nullptr;
                tmp->right = nullptr;
                delete tmp;
                size--;
            }
            return true;
        } catch (const Error &) {
            return false;
        }
    }

    bool search_splay(T value) {
        try {
            if (!root) throw Error_of_search("Tree is empty");
            root = splay(root, value);
            return root->key == value;
        } catch (const Error &) {
            return false;
        }
    }
};

#endif