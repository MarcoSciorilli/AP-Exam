/**
 * \file node.h
 * \author
 * \brief header containing the implementation of the binary search tree
*/

#ifndef	__BST_
#define __BST_

#include<memory> // unique_ptr
#include<utility> // pair
#include<functional> // less
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<string>


/**
 * \brief Implementation of the type: binary search tree
 * \tparam K    Key type
 * \tparam V    Value type
 * \tparam CO   Comparison operator typer (default is std::less<K>)
 */
template<class K, class V, class CO=std::less<K>>
class bst
{

    using pair_type=std::pair<const K,V>;
    using key_type=K;
    using value_type=V;
    using reference=V&;

    struct node; //!< Struct holding the bst node type
    //!< bst node type is defined in the header node.h

    std::unique_ptr<node> root; //!< Unique pointer to the root node

    void clone(const std::unique_ptr<node>& node_to_copy);

public:

    CO comp; //!< Comparison operator


    template<class oK, class oV>
    class _iterator; //!< Template class holding the bst iterator type
    //!< bst iterator is defined in the header iterator.h

    using iterator=_iterator<K,V>;
    using const_iterator=_iterator<const K, const V>;

    /**
     * \brief Default constructor of bst class
     */
    bst()=default;

    /**
     * \brief Custom constructor of bst class
     * \param pair  contains the key and value of the first node with which to build the tree (root)
     */
    explicit bst(const pair_type& pair) { root.reset(new node{pair}); }

    /**
     * \brief Custom constructor of bst class
     * \param _key      contains the key of the first node with which to build the tree (root)
     * \param _value    contains the value of the first node with which to build the tree (root)
     */
    bst(key_type&& _key, value_type&& _value) { root.reset(new node{std::make_pair(_key, _value)}); }

    /**
     * \brief Default destructor of bst class
     */
    ~bst()=default;

    /**
     * \brief Copy constructor of bst class
     * \param to_copy  bst object to be copied
     */
    bst(const bst& to_copy) { clone(to_copy.root); }

    /**
     * \brief Copy assignment of bst class
     * \param to_copy   bst object to be copied
     * \return bst&     reference to copied binary search tree
     */
    bst& operator=(const bst& to_copy);

    /**
     * \brief Move constructor of bst class
     * \param move_from  bst object to be moved
     *
     * Creates a bst by moving the root of the input bst
     */
    bst(bst&& move_from): root(std::move(move_from.root)) {}

    /**
     * \brief Move assignment of bst class
     * \param move_from     bst object to be moved
     * \return bst&         reference to moved binary search tree
     */
    bst& operator=(bst&& move_from);

    /**
     * \brief Inserts a new element in the tree
     * \param x                             pair to be inserted of type std::pair<key, value>
     * \return std::pair<iterator,bool>     The function returns a pair of: an iterator pointing to the inserted node,
     * a bool which is true if a new node has been allocated, false if the key is already present in the tree
     */
    std::pair<iterator, bool> insert(const pair_type& x);

    /**
     * \brief Inserts a new element in the tree
     * \param x                             pair to be inserted of type std::pair<key, value>
     * \return std::pair<iterator,bool>     The function returns a pair of:
     * an iterator pointing to the inserted node;
     * a bool which is true if a new node has been allocated, false if the key is already present in the tree
     */
    std::pair<iterator, bool> insert(pair_type&& x);

    /**
     * \brief Inserts a new element in the tree constructed in-place
     * \tparam Types                        types of the parameters passed to build a new element
     * \param args                          parameters passed to build a new element
     * \return std::pair<iterator,bool>     the function returns a pair of:
     * an iterator pointing to the inserted node;
     * a bool which is true if a new node has been allocated, false if the node is already in the tree
     */
    template<class... Types>
    std::pair<iterator,bool> emplace(Types&&... args);

    /**
     * \brief Clears the content of the tree without any memory leak
     */
    void clear();

    /**
     * \brief Points to the "smallest" node
     * \return iterator     an iterator pointing to the leftmost node, i.e. the one with the smallest key
     */
    iterator begin() noexcept;

    /**
     * \brief Points to the "smallest" node
     * \return const_iterator    a const_iterator pointing to the leftmost node i.e. the one with the smallest key
     */
    const_iterator begin() const noexcept;

    /**
     * \brief Points to the "smallest" node
     * \return const_iterator     a const_iterator pointing to the leftmost node, i.e. the one with the smallest key
     */
    const_iterator cbegin() const noexcept;

    /**
     * \brief Points to one past the "biggest" node
     * \return iterator     an iterator pointing to one past the last node, i.e. the node past the one with the larger key
     */
    iterator end() noexcept;

    /**
     * \brief Points to one past the "biggest" node
     * \return const_iterator     a const_iterator pointing to one past the last node, i.e. the node past the one with the larger key
     */
    const_iterator end() const noexcept;

    /**
     * \brief Points to one past the "biggest" node
     * \return const_iterator     a const_iterator pointing to one past the last node, i.e. the node past the one with the larger key
     */
    const_iterator cend() const noexcept;

    /**
     * \brief Finds a node in the bst given a key
     * \param x             Key to be found
     * \return iterator     pointing to the node with that key if the key exists, otherwise it returns an iterator pointing to "nullptr"
     */
    iterator find(const key_type& x);

    /**
     * \brief Finds a node in the bst given a key
     * \param x                   Key to be found
     * \return const_iterator     pointing to the node with that key if the key exists, otherwise it returns a const_iterator pointing to "nullptr"
     */
    const_iterator find(const key_type& x) const;

    /**
     * \brief Overload of the put-to operator, which lets the user print the tree in ascending order of the keys
     * \param os    Stream where to print the content of the tree
     * \param x     bst to be printed
     * \return os   Stream where the content has been sent
     */
    friend
    std::ostream &operator<<(std::ostream &os, const bst &x) {
        for (auto p = x.cbegin(); p != x.cend(); ++p) {
            os << p << "\n";
        }
        os << std::endl;
        return os;
    }

    /**
     * \brief Returns the key and value of the root of the given bst
     * \param x                                     bst to return the info
     * \return std::pair<key_type, value_type>      pair containing the key and the value of the root node
     */
    friend
    auto get_root(const bst& x) {

        auto root_info=std::make_pair(x.root->data.first, x.root->data.second);
        return root_info;

    }

    /**
     * \brief Overload of the [] operator, which lets the user find a value given the key
     * \param x             Key to be found
     * \return value_type&  If the key exists returns a reference to the associated value. Otherwise it adds a new node containing the input key and the default
     * value and returns a reference to the value
     */
    reference operator[](const key_type& x);

    /**
     * \brief Overload of the [] operator, which lets the user find a value given the key
     * \param x             Key to be found
     * \return value_type&  If the key exists returns a reference to the associated value. Otherwise it adds a new node containing the input key and the default
     * value and returns a reference to the value
     */
    reference operator[](key_type&& x);

    /**
     * \brief Erase a node with a given key from the tree
     * \param key    Key of the node to be erased
     */
    void erase(const key_type &key);

    /**
     * \brief Substitute a node with only one child with its child,taking their respective key as input
     * \param x     Key of the node to be erased
     * \param y     Key of the substitute node
     */

    void transplant(const key_type& x,const key_type& y);
    /**
     * \brief Set a node as the child of a given parent node, on the given side.
     * \param x     Key of the parent to be erased
     * \param y     Key of the child node
     * \param side  Side of the child node
     */

    void new_child(const key_type& x,const key_type& y,bool side);
    /**
     * \brief Given a key of a node, it returns the side of the node relative to its parent
     * \param x     Key of the node
     * \return A boolean: false if the node is on the left side, true if the node is on the right side
     */

    bool child_side(const key_type &x);

    /**
     * \brief Erase a node from the tree
     * \param N     pointer to a node of the tree
     */
    void erase_node(node* N);

    /**
     * \brief Balances the bst, i.e. re-structures the tree in order
     * to minimize its depth
     */
    void balance();

    void newbalancedtree(std::vector<pair_type>& v, int first, int last);

    /**
     * \brief Makes depth of the node available for the user
     * \param k     key value associated with the node whose depth is requested
     * \return      unsigned int storing the depth of the node identified by the key
     */
    unsigned int node_depth(const key_type& k);

    /**
     * \brief Returns maximum depth of the binary search tree
     * \return      unsigned int storing the depth of the deeper node of the tree
     */
    unsigned int max_depth();

    /**
     * \brief Prints tree structure
     */
    void print_2D();

};

//******************************************
//******************NODE********************
//******************************************

template<class K, class V, class CO>
struct bst<K,V,CO>::node {

    pair_type data; //!< pair of a key and a value, stored in the element of the bst object

    std::unique_ptr<node> left; //!< Unique pointer to the left child of the current element

    std::unique_ptr<node> right; //!< Unique pointer to the right child of the current element

    node* parent; //!< Pointer to the parent node of the current element

    /**
     * \brief Default constructor of node struct
     */
    node()=default;

    /**
     * \brief Custom constructor of node struct
     * \param n     pair of a key and a value to store in the element node
     */
    explicit node(const pair_type& n): data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

    /**
     * \brief Custom destructor of node struct
     * \param n             pair of a key and a value to store in the element node
     * \param new_parent    pointer to a node, which will become the parent of the new element node
     */
    node(const pair_type& n, node* new_parent): data{n},  left{nullptr}, right{nullptr}, parent{new_parent} {}

    /**
     * \brief Default destructor of node struct
     */
    ~node() noexcept=default;

    /**
     * \brief Finds the "smaller" element of the bst object that has the current node as root
     * \return node*    pointer to the leftmost node of the bst object that has the current node as root
     */
    node* findLowest() noexcept {

        // Check iteratively for left children untill the last (that is the "smallest")
        if(left) { return left->findLowest(); }
        return this;

    }

    /**
     * \brief Finds the first right anchestor of the current node
     * \return node*    pointer to the first anchestor node which stands on the left of the current node
     */
    node* findUpper() {

        if(parent) {
            // The parent is the first right anchestor of current node if the latter is its
            // parent's left child.
            if(parent->left.get()==this) { return parent; }
            // Otherwise, an iterative search begins
            return parent->findUpper();
        }

        // If there is no parent return 'parent==nullptr'
        return parent;

    }

    /**
     * \brief Compute the depth of the current node in the tree
     * \return Depth    unsigned int storing the depth of the current node in the tree
     */
    unsigned int depth(unsigned int&& Depth=1) {

        if(parent) {
            // If current node has a parent, depth increases by one
            ++Depth;
            // Iteratively calls this function for the parent's depth
            parent->depth(std::move(Depth));
        }

        return Depth;

    }

};

//******************************************
//****************ITERATOR******************
//******************************************

template<class K, class V, class CO>
template<class oK, class oV>
class bst<K,V,CO>::_iterator {

    friend class bst;

    node* here; //!< Pointer to the current element of the bst object

public:

    using value_type=std::pair<oK,oV>;
    using reference=value_type&;
    using pointer=value_type*;
    using difference_type=std::ptrdiff_t;
    using iterator_category=std::forward_iterator_tag;

    /**
     * \brief Default constructor of iterator class
     */
    _iterator()=default;

    /**
     * \brief Custom constructor of iterator class
     * \param p     pointer to a node
     */
    explicit _iterator(node* p): here{p} {}

    /**
     * \brief Default destructor of iterator class
     */
    ~_iterator()=default;

    /**
     * \brief Pre-increment
     *
     * Overloading of pre-increment operator
     */
    _iterator& operator++() {

        if(here) {
            if(here->right) {
                // If there is a node on current position's right
                // "move" to the position corresponding to the
                // first key larger than the current one
                here=here->right->findLowest();
            } else {
                // Otherwise find first right anchestor
                here=here->findUpper();
            }
        }

        return *this;

    }

    /**
     * \brief Post-increment
     *
     * Overloading of post-increment operator
     */
    _iterator operator++(int) {

        auto old(*this);
        operator++();
        return old;

    }

    /**
     * \brief Equality operator
     *
     * Overloading of equality operator
     */
    bool operator==(const _iterator& other_it) const {return here==other_it.here;}

    /**
     * \brief Inequality operator
     *
     * Overloading of inequality operator
     */
    bool operator!=(const _iterator& other_it) const {return !(*this==other_it);}

    /**
     * \brief Dereference operator
     *
     * Overloading of dereference operator
     */
    reference operator*() {return here->data;}

    /**
     * \brief Arrow operator
     *
     * Overloading of arrow operator
     */
    pointer operator->() {return &(*(*this));}

    /**
     * \brief Overload of the put-to operator, which lets the user print the node pointed to by the iterator
     * \param os    Stream where to print the content of the node poited to by the iterator
     * \param it    iterator pointing to the node of interest
     * \return os   Stream where the content has been sent
     */
    friend
    std::ostream &operator<<(std::ostream &os, const _iterator& it) {
        os << "(" << it.here->data.first << "," << it.here->data.second << ")";
        return os;
    }

};



#include"methods.h"





#endif //__BST_
