#include "Presenter.hpp"
#include "Presenter2.hpp"

int main() {
    Presenter<int> p;
    Presenter2<int> p1;

    Presenter2<int>::count_bst = 0.0;
    Presenter2<int>::count_avl = 0.0;
    Presenter2<int>::count_splay = 0.0;
    Presenter2<int>::count_bst_search = 0.0;
    Presenter2<int>::count_avl_search = 0.0;
    Presenter2<int>::count_splay_search = 0.0;
    Presenter2<int>::count_bst_delete = 0.0;
    Presenter2<int>::count_avl_delete = 0.0;
    Presenter2<int>::count_splay_delete = 0.0;

    p1.test();
    p1.test();
    p1.test();

    p1.test2();
    p1.test2();
    p1.test2();

    p1.test3();
    p1.test3();
    p1.test3();

    double middle_time[9];
    middle_time[0] = Presenter2<int>::count_bst / 3;
    middle_time[1] = Presenter2<int>::count_avl / 3;
    middle_time[2] = Presenter2<int>::count_splay / 3;

    std::cout << "Average time of insert (seconds)" << std::endl;
    std::cout << "BST : " << middle_time[0] << std::endl;
    std::cout << "AVL : " << middle_time[1] << std::endl;
    std::cout << "Splay : " << middle_time[2] << std::endl;

    middle_time[3] = Presenter2<int>::count_bst_search / 3;
    middle_time[4] = Presenter2<int>::count_avl_search / 3;
    middle_time[5] = Presenter2<int>::count_splay_search / 3;

    std::cout << "Average time of search (seconds)" << std::endl;
    std::cout << "BST : " << middle_time[3] << std::endl;
    std::cout << "AVL : " << middle_time[4] << std::endl;
    std::cout << "Splay : " << middle_time[5] << std::endl;

    middle_time[6] = Presenter2<int>::count_bst_delete / 3;
    middle_time[7] = Presenter2<int>::count_avl_delete / 3;
    middle_time[8] = Presenter2<int>::count_splay_delete / 3;

    std::cout << "Average time of delete (seconds)" << std::endl;
    std::cout << "BST : " << middle_time[6] << std::endl;
    std::cout << "AVL : " << middle_time[7] << std::endl;
    std::cout << "Splay : " << middle_time[8] << std::endl;

    return 0;
}