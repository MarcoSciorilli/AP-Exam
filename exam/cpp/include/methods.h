#include<memory>
#include<utility>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "bst.h"
#include "node.h"
#include "iterators.h"

template<class K, class V, class CO>
std::pair<iterator, bool> bst<K, V, CO>::insert(pair&& x)
{
    node* here = root.get();
    node* parent = nullptr;   
    // if there is no root node, i create one
    if(root == nullptr)
    {	
    	root.reset(new node(std::forward<pair_type>(x),parent))
		return std::pair<K, V>(iterator{here}, true);
    }
    // Navigate through the tree until i find che correct parent node

    while (here != nullptr){
        

        parent = here;
        //if a node with the same key already exist, return the boolean saying that the new node was not created
        if (!comp(x.first,here->data.first) && !comp(x.first,here->data.first)){
        	return std::pair<K, V>(iterator{here}, false);
        }
        else if (comp(x.first,here->data.first)) {
            here = here->left;
        }
        else {
            here = here->right;
        }

    }

    //create the new node depending on the parent node previously found
    if (comp(x.first,parent->data.first))
        parent->left.reset(new node(std::forward<pair_type>(x),parent));
    	return std::pair<K, V>(iterator{parent->left.get()}, true);
    else
        parent->right.reset(new node(std::forward<pair_type>(x),parent));
    	return std::pair<K, V>(iterator{parent->right.get()}, true);

}



template<class K, class V, class CO>
void bst<K, V, CO>::balance(){
    std::vector<std::pair<K,V>> v;
    iterator first{this->begin()};
    iterator last{this->end()};
    if(first==last)//tree is Empty
        return v;
    else
    {
        while(first<last) {
            v.push_back(*first);
            ++first;
        }
    }
    clear();
    newbalancedtree(v, 0, v.size()-1);
}
//built a balanced tree from an vector of node
template<class K, class V, class CO>
void bst<K, V, CO>::newbalancedtree(std::vector<pair> &v, int first, int last) {
    if(last==v.size()-1){ //si può spostare in balance, ed evitre confonti inutili, ma non si può inserire un vettore qualsiasi
        std::sort( v.begin(), v.end() );
    }
    if(first==last){
        return;
    }

    int middle = (first+last)/2;
    insert(v[middle]);
    newbalancedtree(v, first,middle-1);
    newbalancedtree(v, middle+1, last);
}





















