/**
 * \file node.h
 * \author
 * \brief header containing the implementation of the bst node
*/


#include<memory> //unique_ptr
#include<utility> //pair

template<class N>
struct node {
    // Data contained in the node
    N data;
    using value_type = N;

    // Unique pointer to the left node
    std::unique_ptr<node> left;
    // Unique pointer to the right node
    std::unique_ptr<node> right;

    // Raw pointer to the parent node
    node* parent;
    
    /**
     * \brief Default constructor for the class node.
    */
    node();

    /**
     * \brief Custom constructor for the class node
     * \param n Data to be inserted in the node
     * 
     * Initializes a node with its data
    */
    node(N n) 
    : data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

    /**
     * \brief Custom constructor for the class node
     * \param n Data to be inserted in the node
     * \param p Parent of the node
     * 
     * Initializes a node with data and parent node
    */
    node(N n, node* p)
    : data{n}, left{nullptr}, right{nullptr}, parent{p} {}

    /**
     * \brief Copy constructor for the class node
     * \param n Node to be copied
    */
    node(const node& n)
    : data{n.data}, left{nullptr}, right{nullptr}, parent{n.parent} {}

    /**
     * \brief Default destructor of the class node
    */
    ~node() noexcept = default;
};