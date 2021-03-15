#ifndef __METHODS_
#define __METHODS_

#include "bst.h"

//******************************************************
//******************FOLLOW_KEY_ORDER********************
//******************************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::node* bst<K, V, CO>::follow_key_order(const key_type& key, node* N) const noexcept {

    // if key is smaller than the current node's key, go left
	if (comp(key,N->data.first)) {
        N=N->left.get();
    }
    // otherwise, go right
    else if(comp(N->data.first,key)) {
        N=N->right.get();
    }

    return N;

}

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

	return _insert(x);

}

template<class K, class V, class CO>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::insert(pair_type&& x)
{  

    return _insert(std::move(x));

}

template<class K, class V, class CO>
template<class N>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::_insert(N&& x)
{  

    // if there is no root node, i create one
    if(!root)
    {	
    	root.reset(new node{std::forward<N>(x)});
		return std::make_pair<iterator, bool>(iterator{root.get()}, true);
    }

    // navigate through the tree until i find che correct parent node
	node* here=root.get();
    node* parent=nullptr; 

    while (here){
        
        parent=here;
        // if a node with the same key already exist, return the boolean saying that the new node was not created
        if (!comp(x.first, here->data.first) && !comp(here->data.first, x.first))
        {
        	return std::make_pair<iterator, bool>(iterator{here}, false);
        }
        else {

        	here=follow_key_order(x.first,here);

        }

    }

    // given the data and the suitable parent build a new node, to the parent's left or right according to the x's key 
    if (comp(x.first,parent->data.first)) 
    {
        parent->left.reset(new node{std::forward<N>(x), parent});
        return std::make_pair<iterator, bool>(iterator{parent->left.get()}, true);
    }
    else 
    {
    	parent->right.reset(new node{std::forward<N>(x), parent});
        return std::make_pair<iterator, bool>(iterator{parent->right.get()}, true);
    }

}

//*********************************************
//******************EMPLACE********************
//*********************************************

template <class K, class V, class CO>
template<class... Types>
std::pair<typename bst<K, V, CO>::iterator, bool> bst<K, V, CO>::emplace(Types&&... args) { 

	return insert(std::make_pair<const K, V>(std::forward<Types>(args)...)); 

}

//************************************************
//*********************ERASE**********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::erase(const key_type &key){

    iterator my{find(key)}; // have to return the one with no left child
    if(my == end()) {std::cout<<"key is not in the tree"<<std::endl;}
    else {
        node *here= my.here;
        if((here->left.get()== nullptr) && (here->right.get()== nullptr)){
            std::cout<<"no child"<<std::endl; // if no child, erase the node
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

        if(here->left.get() && !(here->right.get())) {
            std::cout<<"one right child"<<std::endl; // if no left child, substitute with left
            transplant(here->data.first, here->right.get()->data.first);
            return;
        }
        if(here->right.get()== nullptr &&(here->left.get()!= nullptr)) {
            std::cout<<"one left child"<<std::endl; // if no left child, substitute with left
            transplant(here->data.first, here->left.get()->data.first);
            return;
        }
        else{
            node* smaller=here->right.get()->findLowest();
            // set left child of smaller as left child of here
            if(child_side(smaller->data.first)){
                smaller->left.release();
                smaller->left.reset(here->left.get());
                here->left.get()->parent = smaller;
            }
            else {
                if (smaller->right.get() != nullptr && here->left.get() != smaller) { // set right child of smaller as left child of smaller's parent
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
                smaller->right.release(); // set smaller right child as right child of there
                smaller->right.reset(here->right.get());
            }

            if(here->parent== nullptr)
            {
                smaller->parent=nullptr;
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
                erase_node(here); //release parent
                return;
            }
        }

    }

}


template<class K, class V, class CO>
void bst<K, V, CO>::transplant(const key_type& x,const key_type& y) {
    iterator one{find(x)};
    iterator two{find(y)}; // have to return the one with no left child
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
    iterator two{find(y)}; // have to return the one with no left child
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

    delete N;

}

//************************************************
//********************BALANCE*********************
//************************************************

template<class K, class V, class CO>
void bst<K, V, CO>::balance() {
    // initialize a vector of nodes
    std::vector<pair_type> v;
    // get the iterators pointing to the first and last element of the tree
    iterator first{this->begin()};
    iterator last{this->end()};
    // it they coincide, the tree is empty, so no need to balance
    if(first==last)
        return;
    // populate the vectors with all the nodes of the tree
    while(first!=last) {
        v.push_back(first.here->data);
        ++first;
    }
    // clear the tree
    clear();
    // create from the vector a new balanced tree
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
typename bst<K, V, CO>::iterator bst<K, V, CO>::find(const key_type& x) noexcept {

	// get pointer to the root
	auto here=root.get();

	while(here) {

		// As long as pointer does not point to 'nullptr', 
		// follow the hierarchy of the keys, utill a match is found
		if (!comp(x, here->data.first) && !comp(here->data.first, x))
        {
        	return iterator{here};
        }
        else {

        	here=follow_key_order(x,here);

        }
	}

	// If no match is found, return the result of the 'end()' function call
	return end();

}

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::find(const key_type& x) const noexcept {

	// get pointer to the root
	auto here=root.get();

	// As long as pointer does not point to 'nullptr', 
	// follow the hierarchy of the keys, utill a match is found
	while(here) {

		if (!comp(x, here->data.first) && !comp(here->data.first, x))
        {
        	return const_iterator{here};
        }
        else {

        	here=follow_key_order(x,here);

        }

	}

	// If no match is found, return the result of the 'end()' function call
	return cend();

}

//***********************************************************
//******************SUBSCRIPTING OPERATOR********************
//***********************************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](const key_type& x) noexcept
{	
	iterator node_found = find(x);
	if(node_found.here)
		return node_found.here->data.second;

	iterator node_inserted = insert(std::make_pair(x, value_type{})).first;
	return node_inserted.here->data.second;
}

template <class K, class V, class CO>
typename bst<K, V, CO>::reference bst<K, V, CO>::operator[](key_type&& x) noexcept
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
bst<K, V, CO>& bst<K, V, CO>::operator=(bst<K, V, CO>&& move_from) noexcept {

	// To move the tree, move its root to new location (current root location)
    root=std::move(move_from.root);
    return *this;

}

//************************************************
//******************NODE_DEPTH********************
//************************************************

template<class K, class V, class CO>
unsigned int bst<K, V, CO>::node_depth(const key_type& k) const noexcept { 

	// Find node (iterator pointing to the node) with requested key; 
    auto it=find(k);
    // Returns depth of the corresponding node
    return it.here->depth(); 

}

//***********************************************
//******************MAX_DEPTH********************
//***********************************************

template<class K, class V, class CO>
unsigned int bst<K, V, CO>::max_depth() const noexcept { 

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

//*****************************************
//******************MAX********************
//*****************************************

template <class K, class V, class CO>
typename bst<K, V, CO>::const_iterator bst<K, V, CO>::max() const noexcept {

    auto here = root.get();

    if(here) { return const_iterator{here->findMax()}; }

    return const_iterator{nullptr};

}

//*******************************************
//******************KEY**********************
//*******************************************

template<class K, class V, class CO>
const typename bst<K, V, CO>::key_type& bst<K, V, CO>::key(typename bst<K, V, CO>::const_iterator it) const noexcept { 

    return it.here->data.first;

}

#endif //__METHODS_