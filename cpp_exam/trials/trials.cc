#include"../include/bst.h"

// overloading of operator put to for std::pair type
template<class F, class S>
std::ostream &operator<<(std::ostream &os, const std::pair<F,S> &x) {
    os << "(" << x.first << "," << x.second << ")" << std::endl;

    return os;
}

int main()
{
	
	try {

		// creation of the tree by insertion of several nodes
		bst<int,int> binary_tree_0{};

		// TESTING INSERT
		auto pair_0=std::make_pair(0, 1);
		std::pair<int, int> pair_1={-3,8};
		std::pair<int, int> pair_2=std::make_pair(4, 2);
		std::pair<int, int> pair_3=std::make_pair(-1, 1);
		std::pair<int, int> pair_4=std::make_pair(6, 12);
		std::pair<int, int> pair_5=std::make_pair(10, 7);
		std::pair<int, int> pair_6=std::make_pair(12, 17);
		std::pair<int, int> pair_7=std::make_pair(-8, 27);

		(void)binary_tree_0.insert(pair_0);
		(void)binary_tree_0.insert(pair_1);
		(void)binary_tree_0.insert(pair_2);
		(void)binary_tree_0.insert(pair_3);
		(void)binary_tree_0.insert(pair_4);
		(void)binary_tree_0.insert(pair_5);
		(void)binary_tree_0.insert(std::move(pair_6));
		(void)binary_tree_0.insert(std::move(pair_7));

		// TESTING ITERATOR
		std::cout << "\n" << "TESTING RANGE-FOR LOOP" << "\n" << std::endl;
		for(const auto& x: binary_tree_0) {
			std::cout << x << "  ";
		}
		std::cout << std::endl;

		std::cout << "\n" << "TESTING DEREFERENCE OPERATOR" << "\n" << std::endl;
		for(auto p = binary_tree_0.cbegin(); p != binary_tree_0.cend(); ++p) {
			std::cout << *p << "  ";
		}
		std::cout << std::endl;

		std::cout << "\n" << "TESTING ARROW OPERATOR" << "\n" << std::endl;
		bst<int,int>* ptr_tree = &binary_tree_0;
		for(auto p = ptr_tree->cbegin(); p != ptr_tree->cend(); ++p) {
			std::cout << *p << "  ";
		}
		std::cout << std::endl;

		// TESTING PUT TO
		std::cout << "\n" << "TESTING PUT TO OPERATOR" << "\n" << std::endl;
		std::cout << "printing binary_tree_0" << "\n";
		std::cout << binary_tree_0;

		// TESTING GET_ROOT
		std::cout << "\n" << "TESTING GET_ROOT" << "\n" << std::endl;
		std::cout << "printing root of binary_tree_0" << "\n";
		std::cout << "(" << "root key: " << get_root(binary_tree_0).first << ", root value: " << get_root(binary_tree_0).second << ")" << "\n" << std::endl;

		// TESTING FIND
		std::cout << "\n" << "TESTING FIND" << "\n" << std::endl;
		auto node_0=binary_tree_0.find(0);
		std::cout << "finding node with key=0 in binary_tree_0" << "\n";
		std::cout << node_0 << "\n" << std::endl;
		auto node_1=binary_tree_0.find(10);
		std::cout << "finding node with key=10 in binary_tree_0" << "\n";
		std::cout << node_1 << "\n" << std::endl;

		// TESTING CTORS
		std::cout << "\n" << "TESTING CONSTRUCTORS" << "\n" << std::endl;
		bst<int,int> binary_tree_1{pair_3};
		std::cout << "printing binary_tree_1" << "\n";
		std::cout << binary_tree_1;

		bst<int,int> binary_tree_1_bis{std::make_pair(12,67)};
		std::cout << "printing binary_tree_1_bis" << "\n";
		std::cout << binary_tree_1_bis;

		// TESTING COPY SEMANTICS
		std::cout << "\n" << "TESTING COPY SEMANTICS" << "\n" << std::endl;
		std::cout << "--" << "TESTING COPY ASSIGNMENT" << "\n" << std::endl;
		binary_tree_1_bis=binary_tree_0;
		std::cout << "printing binary_tree_1_bis" << "\n";
		std::cout << binary_tree_1_bis;

		std::cout << "\n" << "--" << "TESTING COPY CONSTRUCTOR" << "\n" << std::endl;
		bst<int,int> binary_tree_2{binary_tree_0};
		std::cout << "printing binary_tree_2" << "\n";
		std::cout << binary_tree_2;

		bst<int,int> binary_tree_3{binary_tree_0};
		std::cout << "printing binary_tree_3" << "\n";
		std::cout << binary_tree_3;

		std::cout << "\n" << "--" << "TESTING COPY ASSIGNMENT" << "\n" << std::endl;
		binary_tree_2=binary_tree_1;
		std::cout << "printing binary_tree_2 after assignment" << "\n";
		std::cout << binary_tree_2;

		// TESTING MOVE SEMANTICS
		std::cout << "\n" << "TESTING MOVE SEMANTICS" << "\n" << std::endl;
		binary_tree_2=binary_tree_0;

		std::cout << "\n" << "--" << "TESTING MOVE CTOR" << "\n" << std::endl;	
		bst<int,int> binary_tree_2_bis{std::move(binary_tree_2)};
		std::cout << "printing binary_tree_2 after move ctor" << "\n";
		std::cout << binary_tree_2;
		std::cout << "printing binary_tree_2_bis after move ctor" << "\n";
		std::cout << binary_tree_2_bis;

		std::cout << "\n" << "--" << "TESTING MOVE ASSIGNMENT" << "\n" << std::endl;	
		bst<int,int> binary_tree_3_bis{};
		binary_tree_3_bis = std::move(binary_tree_2_bis);
		std::cout << "printing binary_tree_2_bis after move assignment" << "\n";
		std::cout << binary_tree_2_bis;
		std::cout << "printing binary_tree_3_bis after move assignment" << "\n";
		std::cout << binary_tree_3_bis;


		// TESTING EMPLACE
		std::cout << "\n" << "TESTING EMPLACE" << "\n" << std::endl;
		(void)binary_tree_3.emplace(3,5);
		std::cout << "printing binary_tree_3 after emplacement" << "\n";
		std::cout << binary_tree_3;
		std::cout << "printing root of binary_tree_3 after emplacement" << "\n";
		std::cout << "(" << "root key: " << get_root(binary_tree_3).first << ", root value: " << get_root(binary_tree_3).second << ")" << "\n" << std::endl;

		// (void)binary_tree_3.emplace("sette","otto");
		// std::cout << "printing binary_tree_3 after emplacement" << "\n";
		// std::cout << binary_tree_3;

		// TESTING CLEAR
		std::cout << "\n" << "TESTING CLEAR" << "\n" << std::endl;
		binary_tree_3.clear();
		std::cout << "printing binary_tree_3 after clearing tree" << "\n";
		std::cout << binary_tree_3;

		// SUBSCRIPTING OPERATOR
		std::cout << "\n" << "TESTING SUBSCRIPTING OPERATOR" << "\n" << std::endl;
		std::cout << "retrieving value related to key -3 of binary_tree_0" << "\n";
		std::cout << binary_tree_0[-3] << std::endl;

		binary_tree_0[-3] = 25;

		std::cout << "retrieving value related to key -3 of binary_tree_0 after assignment" << "\n";
		std::cout << binary_tree_0[-3] << std::endl;

		std::cout << "retrieving value related to key 11 (which doesnt exist) of binary_tree_0" << "\n";
		std::cout << binary_tree_0[11] << std::endl;

		bst<int,int> binary_tree_4{binary_tree_0};

		// TESTING NODE_DEPTH
		std::cout << "\n" << "TESTING NODE_DEPTH" << "\n" << std::endl;
		std::cout << "depth of node (10,7): " << binary_tree_0.node_depth(10) << std::endl;

		// TESTING MAX_DEPTH
		std::cout << "\n" << "TESTING MAX_DEPTH" << "\n" << std::endl;
		std::cout << "depth of tree: " << binary_tree_0.max_depth() << std::endl;

		// TESTING PRINT_BST
		std::cout <<  "\n" << "TESTING PRINT_2D" << "\n" << std::endl;
		std::cout << "binary_tree_0:" << std::endl;
		print_bst(binary_tree_0);

		// TESTING ERASE
		std::cout << "\n" << "TESTING ERASE" << "\n" << std::endl;
		std::cout << "erase (11,0) from binary_tree_0:" << std::endl;
		binary_tree_0.erase(11);
		std::cout << "binary_tree_0:" << std::endl;
		print_bst(binary_tree_0);

		std::cout << "erase (0,1) from binary_tree_0:" << std::endl;
		binary_tree_0.erase(0);
		binary_tree_0.erase(4);
		std::cout << "binary_tree_0:" << std::endl;
		print_bst(binary_tree_0);

		// TESTING BALANCE
		std::cout << "\n" << "TESTING BALANCE" << "\n" << std::endl;
		std::cout << "balance binary_tree_4:" << std::endl;
		std::cout << "binary_tree_4 was:" << std::endl;
		print_bst(binary_tree_4);
		std::cout << "binary_tree_4 after balance:" << std::endl;
		binary_tree_4.balance();
		print_bst(binary_tree_4);

		// TESTING MAX
		std::cout << "\n" << "TESTING MAX" << "\n" << std::endl;
		std::cout << "max of balanced tree binary_tree_4 is ";
		auto node_2 = binary_tree_4.max();
		std::cout << node_2 << "\n" << std::endl;

		return 0;

	}
	catch (const std::exception& e) {

		std::cerr << e.what() << std::endl;
    	return 1;

	}
	catch (...) {

		std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    	return 2;

	}


}