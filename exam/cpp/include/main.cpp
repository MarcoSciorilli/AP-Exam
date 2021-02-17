#include"bst.h"

int main()
{

    bst<int,int> binary_tree_0{};

    std::pair<int, int> pair_0=std::make_pair(0, 1);
    std::pair<int, int> pair_1=std::make_pair(-3, 8);
    std::pair<int, int> pair_2=std::make_pair(4, 2);
    std::pair<int, int> pair_3=std::make_pair(-1, 1);
    std::pair<int, int> pair_4=std::make_pair(6, 12);
    std::pair<int, int> pair_5=std::make_pair(10, 7);


    (void)binary_tree_0.insert(pair_0);
    (void)binary_tree_0.insert(pair_1);
    (void)binary_tree_0.insert(pair_2);
    (void)binary_tree_0.insert(pair_3);
    (void)binary_tree_0.insert(pair_4);
    (void)binary_tree_0.insert(pair_5);

    // TESTING PUT TO

    std::cout << "printing binary_tree_0" << "\n";
    std::cout << binary_tree_0;

    std::cout << "printing root of binary_tree_0" << "\n";
    std::cout << "(" << "root key: " << get_root(binary_tree_0).first << ", root value: " << get_root(binary_tree_0).second << ")" << "\n" << std::endl;

    // TESTING FIND

    auto node_0=binary_tree_0.find(0);

    std::cout << "finding node with key=0 in binary_tree_0" << "\n";
    std::cout << node_0 << "\n" << std::endl;

    auto node_1=binary_tree_0.find(10);

    std::cout << "finding node with key=10 in binary_tree_0" << "\n";
    std::cout << node_1 << "\n" << std::endl;

    // TESTING CTORS

    bst<int,int> binary_tree_1{pair_3};
    std::cout << "printing binary_tree_1" << "\n";
    std::cout << binary_tree_1;

    bst<int,int> binary_tree_1_bis{std::make_pair(12,67)};
    std::cout << "printing binary_tree_1_bis" << "\n";
    std::cout << binary_tree_1_bis;

    // TESTING COPY SEMANTICS

    binary_tree_1_bis=binary_tree_0;
    std::cout << "printing binary_tree_1_bis" << "\n";
    std::cout << binary_tree_1_bis;

    bst<int,int> binary_tree_2{binary_tree_0};
    std::cout << "printing binary_tree_2" << "\n";
    std::cout << binary_tree_2;

    bst<int,int> binary_tree_3{binary_tree_0};
    std::cout << "printing binary_tree_3" << "\n";
    std::cout << binary_tree_3;

    binary_tree_2=binary_tree_1;
    std::cout << "printing binary_tree_2 after assignment" << "\n";
    std::cout << binary_tree_2;

    // TESTING MOVE SEMANTICS

    binary_tree_2=binary_tree_0;

    std::cout << "\n" << "TESTING MOVE CTOR" << std::endl;
    bst<int,int> binary_tree_2_bis{std::move(binary_tree_2)};
    std::cout << "printing binary_tree_2 after move ctor" << "\n";
    std::cout << binary_tree_2;
    std::cout << "printing binary_tree_2_bis after move ctor" << "\n";
    std::cout << binary_tree_2_bis;

    std::cout << "\n" << "TESTING MOVE ASSIGNMENT" << std::endl;
    bst<int,int> binary_tree_3_bis{};
    binary_tree_3_bis = std::move(binary_tree_2_bis);
    std::cout << "printing binary_tree_2_bis after move assignment" << "\n";
    std::cout << binary_tree_2_bis;
    std::cout << "printing binary_tree_3_bis after move assignment" << "\n";
    std::cout << binary_tree_3_bis;


    // TESTING EMPLACE

    std::cout << "\n" << "TESTING EMPLACE" << std::endl;
    (void)binary_tree_3.emplace(3,5);
    std::cout << "printing binary_tree_3 after emplacement" << "\n";
    std::cout << binary_tree_3;
    std::cout << "printing root of binary_tree_3 after emplacement" << "\n";
    std::cout << "(" << "root key: " << get_root(binary_tree_3).first << ", root value: " << get_root(binary_tree_3).second << ")" << "\n" << std::endl;

    // (void)binary_tree_3.emplace("sette","otto");
    // std::cout << "printing binary_tree_3 after emplacement" << "\n";
    // std::cout << binary_tree_3;

    // TESTING CLEAR
    std::cout << "\n" << "TESTING CLEAR" << std::endl;
    binary_tree_3.clear();
    std::cout << "printing binary_tree_3 after clearing tree" << "\n";
    std::cout << binary_tree_3;

    // SUBSCRIPTING OPERATOR

    std::cout << "retrieving value related to key -3 of binary_tree_0" << "\n";
    std::cout << binary_tree_0[-3] << std::endl;

    std::cout << "retrieving value related to key 11 (which doesnt exist) of binary_tree_0" << "\n";
    std::cout << binary_tree_0[11] << std::endl;

    bst<int,int> binary_tree_4{binary_tree_0};

    // TESTING NODE_DEPTH
    std::cout << "\n" << "TESTING NODE_DEPTH" << std::endl;
    std::cout << "depth of node (10,7): " << binary_tree_0.node_depth(10) << std::endl;

    // TESTING MAX_DEPTH
    std::cout << "\n" << "TESTING MAX_DEPTH" << std::endl;
    std::cout << "depth of tree: " << binary_tree_0.max_depth() << std::endl;

    // TESTING PRINT_2D
    std::cout << "\n" << "TESTING PRINT_2D" << std::endl;
    std::cout << "binary_tree_0:" << std::endl;
    binary_tree_0.print_2D();

    // TESTING ERASE
    std::cout << "\n" << "TESTING ERASE" << std::endl;
    std::cout << "erase (11,0) from binary_tree_0:" << std::endl;
    binary_tree_0.erase(11);
    std::cout << "binary_tree_0:" << std::endl;
    binary_tree_0.print_2D();

    std::cout << "erase (0,1) from binary_tree_0:" << std::endl;
    binary_tree_0.erase(0);
    binary_tree_0.erase(4);
    std::cout << "binary_tree_0:" << std::endl;
    binary_tree_0.print_2D();

    // TESTING ERASE
    std::cout << "\n" << "TESTING BALANCE" << std::endl;
    std::cout << "balance binary_tree_4:" << std::endl;
    std::cout << "binary_tree_3 was:" << std::endl;
    binary_tree_4.print_2D();
    std::cout << "binary_tree_3 after balance:" << std::endl;
    binary_tree_4.balance();
    binary_tree_4.print_2D();

    return 0;

}