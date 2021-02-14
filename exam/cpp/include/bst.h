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
#include"node.h"
#include"iterators.h"


template<class K, class V, class CO=std::less<K>>
class bst
{

	using pair=std::pair<K,V>;

    struct node;

    std::unique_ptr<node> root;

    public:
    CO comp;
    template<class oK, class oV>
    class _iterator;

    using iterator=_iterator<K,V>;
    using const_iterator=_iterator<const K, const V>;

    bst()=default;

    ~bst()=default;

    bst(const bst& to_copy) {

    	if(to_copy.root) { root.reset(new node{to_copy.root}); }

    }

    bst& operator=(const bst& to_copy) {

    	auto auxiliary{to_copy};
    	*this=std::move(auxiliary);
    	return *this;

    }
    std::pair<iterator, bool> insert(pair&& x);
    void newbalancedtree (std::vector<pair>& v, int first, int last);  // da mettere forse in private??
    void balance();
    void erase(K& key);


};

//******************************************
//******************NODE********************
//******************************************

template<class K, class V, class CO>
struct bst<K,V,CO>::node {

    pair data;

    std::unique_ptr<node> left;

    std::unique_ptr<node> right;

    node* parent;

    node()=default;

    explicit node(pair n): data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

    node(pair n, node* new_parent): data{n},  left{nullptr}, right{nullptr}, parent{new_parent} {}

    ~node() noexcept=default;

    explicit node(const std::unique_ptr<node>& copy_from):
    data{copy_from->data}, left{nullptr}, right{nullptr}, parent{nullptr} {

    	if(copy_from->left) { left.reset(new node{copy_from->left}); }
    	if(copy_from->right) { left.reset(new node{copy_from->right}); }

    }

    node* findLowest() noexcept {

        if(left) return left->findLowest();
        return this;

    }

    node* findUpper() noexcept {

        if(parent){
            if(parent->left==this) return parent;
            return parent->findUpper();
        }
    	return parent;

    }

};

//******************************************
//****************ITERATOR******************
//******************************************

template<class K, class V, class CO>
template<class oK, class oV>
class bst<K,V,CO>::_iterator {

	//using node=typename bst<K,V,CO>::node;

    node* here;

    public:

    	using value_type=std::pair<oK,oV>;
    	using reference=value_type&;
    	using pointer=value_type*;
    	using difference_type=std::ptrdiff_t;
    	using iterator_category=std::forward_iterator_tag;

	    _iterator()=default;

	    explicit _iterator(node* p): here{p} {}

	    ~_iterator()=default;

	    _iterator& operator++() {
	        if(here) {
	            if(here->right) { 
	                here=here->right->findLowest();
	            } else {
	                here = here->findUpper();
	            }
	        }
	        return *this;
	    }

	    _iterator operator++(int) {
	        auto old(*this);
	        operator++();
	        return old;
	    }

	    bool operator==(const _iterator& other_it) {return here==other_it.here;}

	    bool operator!=(const _iterator& other_it) {return *this != other_it;}

	    reference operator*() {return here->data;}

	    pointer operator->() {return &(*(*this));}


};




#include"methods.h"





#endif //__BST_
