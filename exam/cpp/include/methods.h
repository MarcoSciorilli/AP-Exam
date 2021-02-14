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
        return;
    else
    {
        while(first<last) {
            v.push_back(first.here->data);
            ++first;
        }
    }
    clear();
    newbalancedtree(v, 0, v.size()-1);
}
//built a balanced tree from an vector of node
template<class K, class V, class CO>
void bst<K, V, CO>::newbalancedtree(std::vector<pair> &v, int first, int last) {
    if(first==last){
        return;
    }
    int middle = (first+last)/2;
    insert(v[middle]);
    newbalancedtree(v, first,middle-1);
    newbalancedtree(v, middle+1, last);
}








template<class K, class V, class CO>
void bst<K, V, CO>::erase(key_type& key) {

    iterator my{find(key)}; //have to return the one with no left child
    if(my == end()) {std::cout<<"key is not in the tree"<<std::endl;}
    else {
        node* here = my.node();
    }
    if((here->left== nullptr) && (here->right== nullptr)){ //if no child, erase the node
        here->erase_node();
        return;
    }
    if(here->left== nullptr) {          //if no left child, substitute with left
        trasplante(here->data.first, here->right->data.first);
        return;
    }
    if(here->right== nullptr) {         //if no left child, substitute with left
        trasplante(here->data.first, here->left->data.first);
        return;
    }
    else{
    node* smaller=here->right->findLowest(); //find the smaller node to the right of the one to erase
    here->data.first=smaller->data.first;
    here->data.second=smaller->data.second;
    if(smaller->right==nullptr){ //if the smaller node has no child, erase it
        smaller->erase_node();
        return;
    }
    else{   //if it has a right child, substitute smaller with its child
        smaller->right->parent=smaller->parent;
        smaller->perent->left=smaller->right;
        smaller->erase_node();
        return;
    }
    }

}








template<class K, class V, class CO>
void bst<K, V, CO>::transplant(key_type& x,key_type& y) {
    iterator one{find(x)};
    iterator two{find(y)};//have to return the one with no left child
    node* here_one = one.node();
    node* here_two = two.node();
    if(here_one->parent== nullptr){
    root=here_two;
    here_one->erase_node();
    return;
    }
    else{
    bool side{child_side(here_one->data.first)};
    new_child(here_one->parent->data.first,here_two->data.first, side);
    here_one->erase_node();
    }
    return;
}

void bst<K, V, CO>::new_child(key_type& x,key_type& y,bool side) {
    iterator one{find(x)};
    iterator two{find(y)};//have to return the one with no left child
    node* here_one = one.node();
    node* here_two = two.node();
    if(side==false){
    here_one->left=here_two;
    }
    else{
    here_one->right=here_two;
    }
    here_two->parent=here_one;
    return;
}


void bst<K, V, CO>::child_side(key_type& x) {
    iterator my{find(key)};
    node* here = my.node();
    if (here->parent->right == here)
    return 1;
    else{
    return 0;
    }
}












