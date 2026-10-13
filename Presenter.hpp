#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <fstream>
#include <chrono>
#include "BST.hpp"
#include "AVL.hpp"
#include "Splay_tree.hpp"
#include "Read_from_file.hpp"

template <class T>
class Presenter {
private:
    BST<T> *tree;
    AVL<T> *tree1;
    Splay_tree<T> *tree2;
    Read_from_file<T> reader;

public:
    Presenter() : tree(nullptr), tree1(nullptr), tree2(nullptr) {}

    ~Presenter() {
        if (tree) delete tree;
        if (tree1) delete tree1;
        if (tree2) delete tree2;
    }

    void test() {
        std::ofstream f1("test1.txt");
        f1 << "1 2 3 4 5 6  \n";
        f1.close();

        std::ofstream f2("test2.txt");
        f2 << "1 193 252 347 888 888 123 124 1 2 1 9\n";
        f2.close();

        int n = 9;
        tree = new BST<T>();
        reader.set_filename("test1.txt");
        auto start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree(tree);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;
        tree->print_tree();
        tree->delete1(0);
        if (tree->search(n))
            std::cout << "Succesfully!" << std::endl
                      << "The value " << n << " exists in " << tree->get_tree() << std::endl;

        delete tree;
        tree = nullptr;

        tree1 = new AVL<T>();
        reader.set_filename("test1.txt");
        start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree1(tree1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> davl = end - start;
        std::cout << "Time taken by function: " << davl.count() << " seconds" << std::endl;
        tree1->print_tree();
        tree1->insert(1);
        tree1->print_tree();
        tree1->delete1(0);
        if (tree1->search(n))
            std::cout << "Succesfully!" << std::endl
                      << "The value " << n << " exists in " << tree1->get_tree() << std::endl;

        delete tree1;
        tree1 = nullptr;

        tree2 = new Splay_tree<T>();
        reader.set_filename("test1.txt");
        start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree(tree2);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dsplay = end - start;
        std::cout << "Time taken by function: " << dsplay.count() << " seconds" << std::endl;
        tree2->print_tree();
        if (tree2->search_splay(n))
            std::cout << "Succesfully!" << std::endl
                      << "The value " << n << " exists in " << tree2->get_tree() << std::endl;
        tree2->delete1(n);
        tree2->print_tree();
        tree2->delete1(0);
        delete tree2;
        tree2 = nullptr;
    }
};

#endif