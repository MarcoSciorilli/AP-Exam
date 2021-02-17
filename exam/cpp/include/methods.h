#ifndef __METHODS_
#define __METHODS_

#include "bst.h"

//*******************************************
//******************BEGIN********************
//*******************************************

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
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::begin() const noexcept
{

    if (root)
    {
        return const_iterator{ root->findLowest() };
    }
    return const_iterator{ nullptr };

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

//*****************************************
//******************END********************
//*****************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::end() noexcept
{

    return iterator{ nullptr };

}


template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::end() const noexcept
{

    return const_iterator{ nullptr };

}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::cend() const noexcept
{

    return const_iterator{ nullptr };

}

//********************************************
//******************INSERT********************
//********************************************

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

    if (comp(x.first,parent->data.first)) {
        parent->left.reset(new node{x, parent});
        return std::make_pair(iterator{parent->left.get()}, true);
    }
    else {
        parent->right.reset(new node{x, parent});
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

    if (comp(x.first,parent->data.first))
    {
        parent->left.reset(new node{std::forward<pair_type>(x), parent});
        return std::make_pair<iterator, bool>(iterator{parent->left.get()}, true);
    }
    else
    {
        parent->right.reset(new node{std::forward<pair_type>(x), parent});
        return std::make_pair<iterator, bool>(iterator{parent->right.get()}, true);
    }

}


//************************************************
//******************ERASE********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::erase(const key_type &key){
    //Get the iterator pointing to my key
    iterator my{find(key)};
    //If the key is not present in the tree, return a message
    if(my == end()) {std::cout<<"key is not in the tree"<<std::endl;}
    else {
        //Get a pointer to the node to erase, and call it "here"
        node *here= my.here;
        //Node with 0 child
        if(!(here->left.get()) && !(here->right.get())){
            //If here is a right child, release the right node of its parent, and erase it
            if(child_side(here->data.first)){
                here->parent->right.release();
                erase_node(here);
                return;
            }
                //If here is a right child, release the right node of its parent, and erase it
            else {
                here->parent->left.release();
                erase_node(here);
                return;
            }
        }
        //Node with 1 child, on the right
        if(!(here->left.get()) && (here->right.get())) {
            //Substitute here with its right node
            transplant(here->data.first, here->right.get()->data.first);
            return;
        }
        //Node with 1 child, on the left
        if(!(here->right.get()) && (here->left.get())) {
            //Substitute here with its left node
            transplant(here->data.first, here->left.get()->data.first);
            return;
        }
            //Node with 2 child
        else{
            //Find the node with the smallest key on the right branch of the node, and I call it "smaller"
            node* smaller=here->right.get()->findLowest();
            //If smaller is the right node of its parent
            if(child_side(smaller->data.first)){
                //Reset smaller's left node to here's left node
                smaller->left.release();
                smaller->left.reset(here->left.get());
                //Reset here's left node parent to smaller
                here->left.get()->parent = smaller;
            }
                //If smaller is the left node of its parent
            else {
                //If smaller has a right node, and here is not its parent
                if (smaller->right.get() && here->left.get() != smaller) {
                    //Set smaller right node's parent to smaller's parent
                    smaller->right.get()->parent = smaller->parent;
                    //Reset smaller's parent left node, to smaller's right node
                    smaller->parent->left.release();
                    smaller->parent->left.reset(smaller->right.get());
                    //Reset smaller's left node to here's left node
                    smaller->left.release();
                    smaller->left.reset(here->left.get());
                }
                //If smaller has a right node, and here is its parent
                if (smaller->right.get()  && here->left.get() == smaller) {
                    //Reset smaller left node to its own right node
                    smaller->left.release();
                    smaller->left.reset(smaller->right.get());
                }
                //If smaller has no right node, and here is not its parent
                if (!(smaller->right.get()) && here->left.get() != smaller) {
                    //Reset smaller's left node to here's right node
                    smaller->left.release();
                    smaller->left.reset(here->left.get());
                    //Release smaller's parent left node
                    smaller->parent->left.release();
                    smaller->parent->left.reset();
                }
                    //If smaller has no right node, and here is its parent
                else {
                    //Release smaller left node
                    smaller->left.release();
                    smaller->left.reset();
                }
                //Reset smaller's right node to here's right node
                smaller->right.release();
                smaller->right.reset(here->right.get());
            }
            //If here is a root
            if(!(here->parent)){
                //Set smaller parent to nullpointer, reset root to smaller, and erase here
                smaller->parent=nullptr;
                root.release();
                root.reset(smaller);
                erase_node(here);
                return;
            }
                //If here has a parent
            else{
                //If here is a right node
                if(here->parent->right.get() == here){
                    //Reset here's parent's right node to smaller
                    here->parent->right.release();
                    here->parent->right.reset(smaller);
                }
                    //If here is a left node
                else{
                    //Reset here's parent's left node to smaller
                    here->parent->left.release();
                    here->parent->left.reset(smaller);
                }
                //Set smaller's parent node to here's parent node
                smaller->parent=here->parent;
                //Erease here
                erase_node(here);
                return;
            }
        }
    }
}


//************************************************
//******************TRANSPLANT********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::transplant(const key_type& x,const key_type& y){
//Get the pointers to the target node, and to the substitute node
iterator one{find(x)};
iterator two{find(y)};
node* here_one = one.here;
node* here_two = two.here;
//If the target node is the root, reset to root to substitute, and erase the target
if(!(here_one->parent)){
root.release();
root.reset(here_two);
erase_node(here_one);
}
else{
//Get the side of the target relative to its parent
bool side{child_side(here_one->data.first)};
//Set the substitute as child of the right child to the parent of the target
new_child(here_one->parent->data.first,here_two->data.first, side);
//Erase target
erase_node(here_one);
}
}

//************************************************
//******************NEW_CHILD********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::new_child(const key_type& x,const key_type& y,bool side) {
    //Get the pointers to the parent node, to the child node, and to the side to set the child
    iterator one{find(x)};
    iterator two{find(y)};
    node* here_one = one.here;
    node* here_two = two.here;
    //If it is the left side, reset parent's left node to child node
    if(!side){
        here_one->left.release();
        here_one->left.reset(here_two);
    }
        //If it is the right side, reset parent's right node to child node
    else{
        here_one->right.release();
        here_one->right.reset(here_two);
    }
    //Set child's parent node to parent
    here_two->parent= here_one;
}

//************************************************
//******************CHILD_SIDE********************
//************************************************
template<class K, class V, class CO>
bool bst<K, V, CO>::child_side(const key_type &x) {
    //Find the pointer to the node
    iterator my{find(x)};
    node* current = my.here;
    //If the node is a right child, return true
    if (current->parent->right.get() == current){
        return true;
    }
        //If the node is a left child, return false
    else{
        return false;
    }
}

//************************************************
//******************ERASE_NODE********************
//************************************************
template<class K, class V, class CO>
void bst<K, V, CO>::erase_node(bst<K, V, CO>::node *N) {
    //Erase node's left, right and parent node
    N->left.release();
    N->right.release();
    N->parent=nullptr;
}


#endif //__METHODS_
//************************************************
//********************BALANCE*********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::balance() {

    std::vector<pair_type> v;
    iterator first{this->begin()};
    iterator last{this->end()};
    if(first==last)//tree is Empty
        return;
    while(first!=last) {
        v.push_back(first.here->data);
        ++first;
    }

    clear();
    newbalancedtree(v, 0, v.size());

}

// build a balanced tree from an vector of node
template<class K, class V, class CO>
void bst<K, V, CO>::newbalancedtree(std::vector<pair_type>& v, int first, int last) {

    if (first == last) {
        return;
    }
    int middle = (first+last)/2;
    insert(v[middle]);
    newbalancedtree(v, first, middle);
    newbalancedtree(v, middle+1, last);

}

//*******************************************
//******************CLEAR********************
//*******************************************

template <class K, class V, class CO>
void bst<K, V, CO>::clear()
{
    root.reset(nullptr);
}

//******************************************
//******************FIND********************
//******************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::iterator bst<K, V, CO>::find(const key_type& x) {

    // get pointer to the root
    auto here=root.get();

    while(here) {

        // As long as pointer does not point to 'nullptr',
        // follow the hierarchy of the keys, utill a match is found
        if (!comp(x, here->data.first) && !comp(here->data.first, x))
        {
            return iterator{here};
        }
        else if (comp(x,here->data.first))
        {
            here=here->left.get();
        }
        else
        {
            here=here->right.get();
        }

    }

    // If no match is found, return the result of the 'end()' function call
    return end();

}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::find(const key_type& x) const {

    // get pointer to the root
    auto here=root.get();

    // As long as pointer does not point to 'nullptr',
    // follow the hierarchy of the keys, utill a match is found
    while(here) {

        if (!comp(x, here->data.first) && !comp(here->data.first, x))
        {
            return const_iterator{here};
        }
        else if (comp(x,here->data.first))
        {
            here=here->left.get();
        }
        else
        {
            here=here->right.get();
        }

    }

    // If no match is found, return the result of the 'end()' function call
    return cend();

}

//***********************************************************
//******************SUBSCRIPTING OPERATOR********************
//***********************************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](const key_type& x)
{
    iterator node_found = find(x);
    if(node_found.here)
        return node_found.here->data.second;

    iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
    return node_inserted.here->data.second;
}

template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](key_type&& x)
{
    iterator node_found = find(std::move(x));
    if (node_found.here)
        return node_found.here->data.second;

    iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
    return node_inserted.here->data.second;
}

//*******************************************
//******************CLONE********************
//*******************************************

template<class K, class V, class CO>
void bst<K, V, CO>::clone(const std::unique_ptr<typename bst<K,V,CO>::node>& node_to_copy) {

    // Check if passed unique pointer points to null pointer
    if(node_to_copy) {
        // If it does not, insert a new element using node_to_copy's data
        (void)insert(node_to_copy->data);
        // Re-do the above for node_to_copy's children
        clone(node_to_copy->left);
        clone(node_to_copy->right);
    }

}

//*****************************************************
//******************COPY ASSIGNMENT********************
//*****************************************************

template<class K, class V, class CO>
bst<K, V, CO>& bst<K, V, CO>::operator=(const bst<K, V, CO>& to_copy) {

    // Create an auxiliary element using the already defined copy ctor
    auto auxiliary{to_copy};
    // Move content of the auxiliary element to the current element
    *this=std::move(auxiliary);
    return *this;

}

//*****************************************************
//******************MOVE ASSIGNMENT********************
//*****************************************************

template<class K, class V, class CO>
bst<K, V, CO>& bst<K, V, CO>::operator=(bst<K, V, CO>&& move_from) {

    // To move the tree, move its root to new location (current root location)
    root=std::move(move_from.root);
    return *this;

}

//************************************************
//******************NODE_DEPTH********************
//************************************************

template<class K, class V, class CO>
unsigned int bst<K, V, CO>::node_depth(const key_type& k) {

    // Find node (iterator pointing to the node) with requested key;
    auto it=find(k);
    // Returns depth of the corresponding node
    return it.here->depth();

}

//***********************************************
//******************MAX_DEPTH********************
//***********************************************

template<class K, class V, class CO>
unsigned int bst<K, V, CO>::max_depth() {

    // Initialize maximum depth with the depth of the "smallest" node of the tree
    auto max=node_depth(cbegin().here->data.first);
    // Compute depth for each node and find the maximum
    unsigned int depth_here{};
    for (auto p = cbegin(); p != cend(); ++p) {
        depth_here=node_depth(p.here->data.first);
        if(max<depth_here) max=depth_here;
    }

    return max;

}

//************************************************
//******************PRINT_2D********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::print_2D() {

    // Traverse the tree following the key order:
    // For each element, compute its depth and print
    // as many spaces as the computed depth plus some
    // extra spaces needed for deeper nodes in order
    // not to print the to close to the others.
    for (auto p = cbegin(); p != cend(); ++p) {
        auto n_spaces=p.here->depth();
        auto extra_spaces=n_spaces;

        std::cout << "\n";

        while(n_spaces-1) {
            std::cout << "     ";
            while(extra_spaces) {
                std::cout << "     ";
                --extra_spaces;
            }
            --n_spaces;
        }

        std::cout << p << "\n";

    }

    std::cout << std::endl;

}











#endif //__METHODS_





