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

template<class K, class V, class CO=std::less<K>>
class bst
{

    using pair_type=std::pair<const K,V>;
    using key_type=K;
    using value_type=V;
    using reference=V&;

    struct node;

    std::unique_ptr<node> root;

    void transplant(const key_type& x,const key_type& y);

    void new_child(const key_type& x,const key_type& y,bool side);

    bool child_side(const key_type& x);

public:

    CO comp;

    template<class oK, class oV>
    class _iterator;

    using iterator=_iterator<K,V>;
    using const_iterator=_iterator<const K, const V>;

    bst()=default;

    explicit bst(const pair_type& pair) { root.reset(new node{pair}); }

    explicit bst(pair_type&& pair) { root.reset(new node{std::move(pair)}); }

    bst(key_type&& _key, value_type&& _value) {

        root.reset(new node{std::make_pair(_key, _value)});

    }

    ~bst()=default;

    bst(const bst& to_copy) {

        if(to_copy.root) { root.reset(new node{to_copy.root}); }

    }

    bst& operator=(const bst& to_copy) {

        auto auxiliary{to_copy};
        *this=std::move(auxiliary);
        return *this;

    }

    bst(bst&& move_from): root(std::move(move_from.root)) { move_from.root.reset(nullptr); }

    bst& operator=(bst&& move_from) {

        root=std::move(move_from.root);
        move_from.root.reset(nullptr);
        return *this;

    }

    std::pair<iterator, bool> insert(const pair_type& x);

    std::pair<iterator, bool> insert(pair_type&& x);

    template<class... Types>
    std::pair<iterator,bool> emplace(Types&&... args);

    iterator begin() noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept;

    const_iterator cend() const noexcept;

    iterator find(const key_type& x);

    const_iterator find(const key_type& x) const;

    friend
    std::ostream &operator<<(std::ostream &os, const bst &x) {
        for (auto p = x.cbegin(); p != x.cend(); ++p) {
            os << p << "\n";
        }
        os << std::endl;
        return os;
    }

    friend
    auto get_root(const bst& x) {

        auto root_info=std::make_pair(x.root->data.first, x.root->data.second);
        return root_info;

    }

    reference operator[](const key_type& x);

    reference operator[](key_type&& x);

    void clear();

    void erase_node(typename bst<K,V,CO>::node* N);

    void erase(const key_type& key);

};

//******************************************
//******************NODE********************
//******************************************

template<class K, class V, class CO>
struct bst<K,V,CO>::node {

    pair_type data;

    std::unique_ptr<node> left;

    std::unique_ptr<node> right;

    node* parent;

    node()=default;

    explicit node(const pair_type& n): data{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}

    node(const pair_type& n, node* new_parent): data{n},  left{nullptr}, right{nullptr}, parent{new_parent} {}

    ~node() noexcept=default;

    explicit node(const std::unique_ptr<node>& copy_from):
            data{copy_from->data}, left{nullptr}, right{nullptr}, parent{nullptr} {

        if(copy_from->left) { left.reset(new node{copy_from->left}); }

        if(copy_from->right) { left.reset(new node{copy_from->right}); }

    }

    node* findLowest() noexcept {

        if(left) { return left->findLowest(); }
        return this;

    }

    node* findUpper() {

        if(parent) {
            if(parent->left.get()==this) { return parent; }
            return parent->findUpper();
        }
        return parent;

    }

    node* rightmost() {

        if(right) { return right->rightmost(); }
        return right.get();

    }

};

//******************************************
//****************ITERATOR******************
//******************************************

template<class K, class V, class CO>
template<class oK, class oV>
class bst<K,V,CO>::_iterator {

    //using node=typename bst<K,V,CO>::node;

    friend class bst;

    node* here;

public:

    using value_type=std::pair<oK,oV>;
    using reference=value_type&;
    using pointer=value_type*;
    using difference_type=std::ptrdiff_t;
    using iterator_category=std::forward_iterator_tag;

    _iterator()=default;

    explicit _iterator(node* p): here{p} {}

    _iterator(const _iterator& other_it): here{other_it.here} {}

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

    bool operator==(const _iterator& other_it) const {return here==other_it.here;}

    bool operator!=(const _iterator& other_it) const {return !(*this==other_it);}

    reference operator*() {return here->data;}

    pointer operator->() {return &(*(*this));}

    friend
    std::ostream &operator<<(std::ostream &os, const _iterator& it) {
        os << "(" << "key: " << it.here->data.first << ", value: " << it.here->data.second << ")";
        return os;
    }

};









#include"methods.h"




#endif //__BST_