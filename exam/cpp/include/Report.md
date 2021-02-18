# Binary Search Tree

The project consists in the implementation of a Binary Search Tree (BST), using the C++ programming language. A BST is a data structure used to store data in an organized way, which also allows to quickly retrieve them.  Generally it is made of nodes, each storing a pair: a *key* and a *value*. A BST is ordered hierarchically so that every node is connected to at most to two other below, called children: the *left* and *right* children. Data are stored based on the comparison between keys: given a current observed node and a new one to insert, if the key of the latter is smaller than the one of former, the new datum  is going to populate the left subtree of the current node,  the right subtree otherwise.

The Binary Search Tree has been implemented in the form of a template class, whose templates are the key type `K`, the value type`V` and the comparison operator type `CO` (set, by default, to ``` std::less<K> ```).  The BST class contains two nested classes, the *node* struct and the *iterator* class, in order to meet the variety of needs associated with this kind of data structure.

Finally, the implemented BST has been benchmarked, comparing its performance to those of some STL data structures, like the ordered and the unordered maps.

## Nested classes

### Struct *node*

```node``` is a struct implemented to mimic the features of a Binary Search Tree node. 

Indeed, this struct has four members:

- ``data`` , a `std::pair<const K, V>` object, which stores the key and the value corresponding to a given node;
- `left` and `right`, that are the left and right children of a given node. Since each node can have at most one left child and one right child it seemed suitable for them to be `std::unique_ptr<node>`.
- `parent`, which is a raw pointer `node*` to the parent node of a give node. It was chosen to be a raw pointer instead of a unique pointer to a node because a node can have two children, each pointing to the same parent node.

As part of this class there are also the default node constructor and destructor and a couple more custom constructors: one that construct a node from a given pair of key and value, and the other that takes also a raw pointer to a node, which will become the new parent of the constructed node.

Finally, three member functions were added:

- `node* findLowest()`:  function built to find the leftmost node belonging to the subtree which has the current node as the root. This function is of utmost importance in the development of the class `_iterator`.
- `node* findUpper()`:  function built to find the first right ancestor of a given node, that is a previously inserted node with the first key larger than the given one. Also `findUpper()` holds a very important role in the implementations of the `_iterator` class.
- `unsigned int depth(unsigned int&& Depth=1)`: recursive function needed to compute the depth of a node in the tree.

`node` was build as a nested class inside the private section of the larger `bst<K, V, CO>`: this choice seemed the most suitable since the BST node is a structure that should not be created nor accessed by the user at any time. There are ways to insert a node into the tree, but there should be no reason to create a BST node without creating a Binary Search Tree, or to access and change some of its important members, such as `left` and `write`.    

### Class *_iterator*

`_iterator<oK, oV>` is a template class, needed to iterate through the a `bst<K, V, CO>` object.  In order to perform all the requested tasks, it was sufficient to implement a *forward* iterator.

`_iterator` contains a private member `here`, which is a pointer to a node. In the public section, a part from the obvious default constructor and destructor, one can find a custom constructor, for constructing an iterator with a pointer to a node, and the overloading of  the pre- and post-increment operators (`++`), for which the definition of the aforementioned `findLowest()` and `findUpper()` is fundamental, the equality and inequality comparison operators (`==`, `!=`), the dereference operator (`*`) and the arrow operator (`->`).

As for the node struct, the iterator class was implemented as a nested class inside the BST template class, since `_iterator<oK, oV>` depends on the structure of the Binary Search Tree itself.



## *bst* template class

The private section of the class `bst<K, V, CO>`  contains the struct `node`, the member `root`, and some member functions that should not be accessible to the user.

### Root

The private member `root` is used to identify the root node of the tree in a unique way. Since every tree has only one root, it was defined as unique pointer to a node.

### Member functions

#### Insert

```c++
//public
    std::pair<iterator, bool> insert(const pair_type& x);
    std::pair<iterator, bool> insert(pair_type&& x);
```

This function is called when the user wants to insert a new node inside the BST. It takes as input an lvalue or an rvalue of a pair key/stored-value, and return an iterator pointing to the node, and a boolean stating the success of the insertion.  If the BST is empty the function insert the node as the root of the tree. Otherwise, the function navigate through the tree until it finds a suitable parent node for the given one. It then compare the key given with the one of the found parent, and set the new node as a *left* or *right* child consequently. If during this process the function finds a node with the same key, it returns an iterator pointing to that node, paired with a *false* boolean.

####  Begin 

```c++
//public
	iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
```

 This function is used to start iterations on the tree. It returns an iterator to the leftmost node, the one with the smallest key. 

#### End

```c++
//public
	iterator end() noexcept;
    const_iterator end() const noexcept;
```

This function is used to finish an iteration on the tree. It returns an iterator pointing to one past the last element of the tree.

#### Clear

```c++
//public
void clear();
```

This function deletes the tree by resetting the `root`.

#### Erase 

```c++
//private 
    void transplant(const key_type& x,const key_type& y);
    void new_child(const key_type& x,const key_type& y,bool side);
    void erase_node(node* N);
//public
	void erase(const key_type &key);
```

This function is called when the user wants to erase a node. It takes as input the key of the node we want to delete. If there isn't any node with that key in the tree, or the tree is empty, a warning message is printed on the screen. Otherwise, the function handle differently every situation which can arise in the erase process:

1. The node has **0 children** and **is the root**: the function clear the three.
2. The node has **0 children** and **is not the root**: the function determine if the node is a left or right child through the use of the helper function `child_side` , reset its parent corresponding left or right pointer to *nullprt* and erase the node through the use of the helper `erase_node`.
3. The node has **1 children**: the function substitute the node with its children through the use of the helper function `transplant`.
4. The node has **2 children**: the function find the node with the smaller key on the right subtree of the node and substitute it to the node itself, and erase the node with the helper `erase_node`. In this case, all different situations are handled depending whether the node to erase is the root or not, and whether the substitute node is the child of the one to erase.

Helper functions:

`transplant`: It takes as input the keys of two nodes, a parent and a child. It gets the pointers to such nodes, check if the parent is root, and in such case reset the root to the child node, and the child node's parent pointer to *nullprt*. Otherwise, it gets the side of the child (left or right) and thanks to the helper function `new_child` it set the child as the child of the parent's parent, and the child's parent as the parent's parent. It than erase parent node with the helper `erase_node`.

`new_child`: It takes as input the keys of two nodes, a parent and a child, and boolean representing the side to set the child to (false for left, true for right). In then handles the pointers of the two nodes in order to create parent-child relation between the two on the indicated side.

`erase_node`: It takes a node as input, it reset to *nullptr* its *left*,*right* and *parent* pointers, and delete the data.

#### Balance

```c++
//private
	void newbalancedtree(std::vector<pair_type>& v, int first, int last);
//public
    void balance();
```

This function is called when the user wants to balance the tree. It stores in an orderly fashion all the node pairs contained in the tree in vector,  it deletes the old tree using the function `clear`, and reconstructs it in a balanced way with the helper function `newbalancedtree`.

Helper function:

`newbalancedtree`: this function takes as input an ordered vector of pair, and two int represent the index of the first and last element of the vector on which the function works.  It computes the median value of the vector considered , and it inserts it in the new tree (with the function `insert`), recalling itself recursively on the two remaining halves of the vector.

#### Child_side

```c++
//public
    bool child_side(const key_type &x);
```

This function takes as input a key of a node, and return a boolean: *false* if the node is a left node, *true* if it is a right node. It achieves so comparing the node pointer with the left and right node pointer of its parent node. 

#### Find

```c++
//public
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
```



#### Copy Semantic

```
code
```

#### Move Semantic

```
code
```

#### Emplace

```
code
```

#### Subscripting operator

```
code
```

#### Put-to operator

```
code
```

#### *Print_2D*

```c++
// public
void print_2D();
```

This function is used to print the structure of the tree on a two-dimensional plane. In order to keep the implementation as simple as possible, the tree is not printed downward, with the root at the top and the deeper nodes at the bottom, but from left to right, with the root as the first node to the left, while left children grow upward and right ones downward.

For example, consider the construction of the following tree:

```c++
std::pair<int, int> pair_0=std::make_pair(4, 2);
std::pair<int, int> pair_1=std::make_pair(10, 7);
std::pair<int, int> pair_2=std::make_pair(-1, 1);
std::pair<int, int> pair_3=std::make_pair(0, 1);
std::pair<int, int> pair_4=std::make_pair(-3, 25);
std::pair<int, int> pair_5=std::make_pair(6, 12);
std::pair<int, int> pair_6=std::make_pair(11, 0);

bst<int,int> binary_tree{};

(void)binary_tree.insert(pair_0);
(void)binary_tree.insert(pair_1);
(void)binary_tree.insert(pair_2);
(void)binary_tree.insert(pair_3);
(void)binary_tree.insert(pair_4);
(void)binary_tree.insert(pair_5);
(void)binary_tree.insert(pair_6);
```

The output of `binary_tree.print_2D();` becomes:

```bash
                         (-3,25)

               (-1,1)

                         (0,1)

(4,2)

                         (6,12)

               (10,7)

                         (11,0)
```

