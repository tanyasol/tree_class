#ifndef PRESENTER2_HPP
#define PRESENTER2_HPP

#include <fstream>
#include <chrono>
#include <random>
#include "BST.hpp"
#include "AVL.hpp"
#include "Splay_tree.hpp"
#include "Read_from_file.hpp"

template <class T>
class Presenter2 {
private:
    BST<T> *tree;
    AVL<T> *tree1;
    Splay_tree<T> *tree2;
    Read_from_file<T> reader;

public:
    Presenter2() : tree(nullptr), tree1(nullptr), tree2(nullptr) {}

    ~Presenter2() {
        if (tree) delete tree;
        if (tree1) delete tree1;
        if (tree2) delete tree2;
    }

    static double count_bst;
    static double count_avl;
    static double count_splay;
    static double count_bst_search;
    static double count_avl_search;
    static double count_splay_search;
    static double count_bst_delete;
    static double count_avl_delete;
    static double count_splay_delete;

    void test() {
        std::ofstream f3("test_time.txt");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-100000, 100000);
        using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

        for (int i = 0; i < 10000; i++)
            f3 << dist(gen) << " ";
        f3.close();

        tree = new BST<T>();
        reader.set_filename("test_time.txt");
        time_point start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree(tree);
        time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        count_bst += duration.count();
        delete tree;
        tree = nullptr;

        tree1 = new AVL<T>();
        reader.set_filename("test_time.txt");
        start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree1(tree1);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> davl = end - start;
        count_avl += davl.count();
        delete tree1;
        tree1 = nullptr;

        tree2 = new Splay_tree<T>();
        reader.set_filename("test_time.txt");
        start = std::chrono::high_resolution_clock::now();
        reader.read_to_tree(tree2);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dsplay = end - start;
        count_splay += dsplay.count();
        delete tree2;
        tree2 = nullptr;
    }

    void test2() {
        std::ofstream f3("test_time.txt");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-100000, 100000);
        int counter = 0;
        using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
        int arr[10000];
        for (int i = 0; i < 10000; i++) {
            int k = dist(gen);
            f3 << k << " ";
            arr[i] = k;
        }
        f3.close();

        tree = new BST<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree(tree);
        time_point start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree->search(arr[i]);
        time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        count_bst_search += duration.count();
        delete tree;
        tree = nullptr;

        tree1 = new AVL<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree1(tree1);
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree1->search(arr[i]);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> davl = end - start;
        count_avl_search += davl.count();
        delete tree1;
        tree1 = nullptr;

        tree2 = new Splay_tree<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree(tree2);
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree2->search_splay(arr[i]);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dsplay = end - start;
        count_splay_search += dsplay.count();
        delete tree2;
        tree2 = nullptr;
    }

    void test3() {
        std::ofstream f3("test_time.txt");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-100000, 100000);
        int counter = 0;
        using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
        int arr[10000];
        for (int i = 0; i < 10000; i++) {
            int k = dist(gen);
            f3 << k << " ";
            arr[i] = k;
        }
        f3.close();

        tree = new BST<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree(tree);
        time_point start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree->delete1(arr[i]);
        time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        count_bst_delete += duration.count();
        delete tree;
        tree = nullptr;

        tree1 = new AVL<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree1(tree1);
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree1->delete1(arr[i]);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> davl = end - start;
        count_avl_delete += davl.count();
        delete tree1;
        tree1 = nullptr;

        tree2 = new Splay_tree<T>();
        reader.set_filename("test_time.txt");
        reader.read_to_tree(tree2);
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) counter += tree2->delete1(arr[i]);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dsplay = end - start;
        count_splay_delete += dsplay.count();
        delete tree2;
        tree2 = nullptr;
    }
};

template <class T> double Presenter2<T>::count_bst = 0.0;
template <class T> double Presenter2<T>::count_avl = 0.0;
template <class T> double Presenter2<T>::count_splay = 0.0;
template <class T> double Presenter2<T>::count_bst_search = 0.0;
template <class T> double Presenter2<T>::count_avl_search = 0.0;
template <class T> double Presenter2<T>::count_splay_search = 0.0;
template <class T> double Presenter2<T>::count_bst_delete = 0.0;
template <class T> double Presenter2<T>::count_avl_delete = 0.0;
template <class T> double Presenter2<T>::count_splay_delete = 0.0;

#endif