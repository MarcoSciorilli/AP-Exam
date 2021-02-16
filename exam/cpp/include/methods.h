#ifndef __METHODS_
#define __METHODS_

#include "bst.h"

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::begin() noexcept
{

    if(root)
    {
        return iterator{ root->findLowest() };
    }
    return iterator{ nullptr };

}


template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cbegin() const noexcept
{

    if (root)
    {
        return const_iterator{ root->findLowest() };
    }
    return const_iterator{ nullptr };

}

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::end() noexcept
{

    return iterator{ nullptr };

}


template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cend() const noexcept
{

    return const_iterator{ nullptr };

}

template <class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(const pair_type& x)
{
    // If the root is null I insert a new node here
    if(!root)
    {
        root.reset(new node{x});
        return std::make_pair(iterator{root.get()}, true);
    }

    node* here=root.get();
    node* parent=nullptr;
    while(here) {

        parent=here;

        // x.key < here.key
        if (comp(x.first, here->data.first))
        {
            here=here->left.get();
        }
            // x.key > here.key
        else if (comp(here->data.first, x.first))
        {
            here=here->right.get();
        }
            // x.key == here.key
        else
        {
            return std::make_pair(iterator{here}, false);
        }

    }

    //create the new node depending on the parent node previously found
    auto auxiliary_node=new node{x, parent};

    if (comp(x.first,parent->data.first)) {
        parent->left.reset(auxiliary_node);
        return std::make_pair(iterator{parent->left.get()}, true);
    }
    else {
        parent->right.reset(auxiliary_node);
        return std::make_pair(iterator{parent->right.get()}, true);
    }


}

template<class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair_type&& x)
{
    // if there is no root node, i create one
    if(!root)
    {
        root.reset(new node{std::forward<pair_type>(x)});
        return std::make_pair<iterator, bool>(iterator{root.get()}, true);
    }

    // Navigate through the tree until i find che correct parent node
    node* here=root.get();
    node* parent=nullptr;

    while (here){

        parent=here;
        //if a node with the same key already exist, return the boolean saying that the new node was not created
        if (!comp(x.first, here->data.first) && !comp(here->data.first, x.first))
        {
            return std::make_pair<iterator, bool>(iterator{here}, false);
        }
        else if (comp(x.first,here->data.first))
        {
            here=here->left.get();
        }
        else
        {
            here=here->right.get();
        }

    }

    //create the new node depending on the parent node previously found
    auto auxiliary_node=new node{std::forward<pair_type>(x), parent};

    if (comp(x.first,parent->data.first))
    {
        parent->left.reset(auxiliary_node);
        return std::make_pair<iterator, bool>(iterator{parent->left.get()}, true);
    }
    else
    {
        parent->right.reset(auxiliary_node);
        return std::make_pair<iterator, bool>(iterator{parent->right.get()}, true);
    }


}

template <class K, class V, class CO>
template<class... Types>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::emplace(Types&&... args) {

    if(std::is_constructible<pair_type, Types...>::value) {
        return insert(std::make_pair<const K, V>(std::forward<Types>(args)...));
    }
    return std::make_pair<typename bst<K, V, CO>::iterator, bool>(typename bst<K, V, CO>::iterator{nullptr},false);

}

template <class K, class V, class CO>
void bst<K, V, CO>::clear()
{
    root.reset(nullptr);
}

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::find(const key_type& x) {

    for (auto p=cbegin(); p!=cend(); ++p) {

        if(!comp(p.here->data.first,x) && !comp(x,p.here->data.first)) {
            return iterator{p.here};
        }

    }

    return end();

}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::find(const key_type& x) const {

    for (auto p=cbegin(); p!=cend(); ++p) {

        if(!comp(p.here->data.first,x) && !comp(x,p.here->data.first)) {
            return const_iterator{p.here};
        }

    }

    return cend();

}

// Insertion with copy
template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](const key_type& x)
{
    iterator node_found = find(x);
    if(node_found.here)
        return node_found.here->data.second;

    iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
    return node_inserted.here->data.second;
}


// Insertion with move
template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](key_type&& x)
{
    iterator node_found = find(std::move(x));
    if (node_found.here)
        return node_found.here->data.second;

    iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
    return node_inserted.here->data.second;
}



template<class K, class V, class CO>
void bst<K, V, CO>::erase(const key_type &key){

    iterator my{find(key)}; //have to return the one with no left child
    if(my == end()) {std::cout<<"key is not in the tree"<<std::endl;}
    else {
        node *here= my.here;
        if((here->left.get()== nullptr) && (here->right.get()== nullptr)){
            std::cout<<"no child"<<std::endl;//if no child, erase the node
            if(child_side(here->data.first)){
                here->parent->right.release();
                erase_node(here);
                return;
            }
            else {
                here->parent->left.release();
                erase_node(here);
                return;
            }
        }

        if(here->left.get() && !(here->right.get()!)) {
            std::cout<<"one right child"<<std::endl;//if no left child, substitute with left
            transplant(here->data.first, here->right.get()->data.first);
            return;
        }
        if(here->right.get()== nullptr &&(here->left.get()!= nullptr)) {
            std::cout<<"one left child"<<std::endl;//if no left child, substitute with left
            transplant(here->data.first, here->left.get()->data.first);
            return;
        }
        else{
            node* smaller=here->right.get()->findLowest();
            std::cout<<smaller->data.first<<std::endl;
            //set left child of smaller as left child of here
            if(child_side(smaller->data.first)){
                smaller->left.release();
                smaller->left.reset(here->left.get());
                here->left.get()->parent = smaller;
            }
            else {
                if (smaller->right.get() != nullptr && here->left.get() != smaller) {   //set right child of smaller as left child of smaller's parent
                    smaller->right.get()->parent = smaller->parent;
                    smaller->parent->left.release();
                    smaller->parent->left.reset(smaller->right.get());
                    smaller->left.release();
                    smaller->left.reset(here->left.get());
                }
                if (smaller->right.get() != nullptr && here->left.get() == smaller) {
                    smaller->left.release();
                    smaller->left.reset(smaller->right.get());
                }
                if (smaller->right.get() == nullptr && here->left.get() != smaller) {
                    smaller->left.release();
                    smaller->left.reset(here->left.get());
                    smaller->parent->left.release();
                    smaller->parent->left.reset();
                } else {
                    smaller->left.release();
                    smaller->left.reset();
                }
                smaller->right.release();              //set smaller right child as right child of there
                smaller->right.reset(here->right.get());
            }

            if(here->parent== nullptr)
            {
                smaller->parent== nullptr;
                root.release();
                root.reset(smaller);
                erase_node(here);
                return;
            }
            else{
                if(here->parent->right.get() == here){
                    here->parent->right.release();
                    here->parent->right.reset(smaller);
                }
                else{
                    here->parent->left.release();
                    here->parent->left.reset(smaller);
                }
                smaller->parent=here->parent;
                erase_node(here);                  //release parent
                return;
            }
        }

    }


}


template<class K, class V, class CO>
void bst<K, V, CO>::transplant(const key_type& x,const key_type& y) {
    iterator one{find(x)};
    iterator two{find(y)};//have to return the one with no left child
    node* here_one = one.here;
    node* here_two = two.here;
    if(here_one->parent== nullptr){
        root.release();
        root.reset(here_two);
        erase_node(here_one);
    }
    else{
        bool side{child_side(here_one->data.first)};
        new_child(here_one->parent->data.first,here_two->data.first, side);
        std::cout<<here_two->data.first<<std::endl;

        erase_node(here_one);
    }
}

template<class K, class V, class CO>
void bst<K, V, CO>::new_child(const key_type& x,const key_type& y,bool side) {
    iterator one{find(x)};
    iterator two{find(y)};//have to return the one with no left child
    node* here_one = one.here;
    node* here_two = two.here;
    if(!side){
        here_one->left.release();
        here_one->left.reset(here_two);
    }
    else{
        here_one->right.release();
        here_one->right.reset(here_two);
    }
    here_two->parent= here_one;
}

template<class K, class V, class CO>
bool bst<K, V, CO>::child_side(const key_type &x) {
    iterator my{find(x)};
    node* current = my.here;
    if (current->parent->right.get() == current){
        return true;
    }
    else{

        return false;
    }
}

template<class K, class V, class CO>
void bst<K, V, CO>::erase_node(bst<K, V, CO>::node *N) {

    N->left.release();
    N->right.release();
    N->parent=nullptr;

}


#endif //__METHODS_







