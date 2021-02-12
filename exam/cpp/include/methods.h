#include<memory>
#include<utility>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


template<class K, class V, class CO>
template<class T>
std::pair<typename bst<K,V,CO>::iterator, bool> bst<K,V,CO>::insert(T&& x)
{
    node* here = root.get();
    node* parent = nullptr;   
    // if there is no root node, i create one
    if(root == nullptr)
    {	
    	root= new node(std::forward<T>(x),parent)
		return std::make_pair(iterator{here}, true);
    }
    // Navigate through the tree until i find che correct parent node

    while (here != nullptr){
        

        parent = here;
        //if a node with the same key already exist, return the boolean saying that the new node was not created
        if (x.first == here->data.first){
        	return std::make_pair(iterator{here}, false);
        }
        else if (x.first < here->data.first) {
            here = here->left;
        }
        else {
            here = here->right;
        }

    }

    //create the new node depending on the parent node previously found
    if (x.first < parent->data.first)
        parent->left = new node(std::forward<T>(x),parent);
    	return std::make_pair(iterator{parent->left.get()}, true);
    else
        parent->right = new node(std::forward<T>(x),parent);
    	return std::make_pair(iterator{parent->right.get()}, true);

}
 //Begin

template<class K, class V, class CO>
typename bst<K,V,CO>::iterator bst<K,V,CO>::begin() 
{		
	if(root)
	{
		node* n = root->findLowest();
		return iterator{n};
	}
	return iterator{ nullptr };

}










