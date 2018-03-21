#ifndef NODE_HH
#define NODE_HH



#include <iostream>

/*
 Class template  that represents node.
*/
template <typename keyType> 
class node
{
 private:
  keyType _key;//Data stored by node
  node<keyType>*   _parent;//Pointer to parent node
  node<keyType>*   _left;  //Pointer to left child
  node<keyType>*   _right; //Pointer to right child
 public:
  node();//Sets pointers to NULL
  node(const keyType initKey);//Sets pointers to NULL, sets _key to desired initial value
  ~node();
  void             setKey(const int& key);//Assigns new value to _key
  int              getKey()    const;//Returns _key value
  void             setParent(node<keyType>* left);//Sets new parent
  node<keyType>*   getParent() const;//Returns pointer to parent node
  void             setLeft(node<keyType>* left);//Sets new left child
  node<keyType>*   getLeft()   const;//Returns pointer to left child
  void             setRight(node<keyType>* right);//Sets new right child
  node<keyType>*   getRight()  const;//Returns pointer to right child
  void             print()     const { std::cout << _key << " "; };//Prints _key
};

template <typename keyType>
node<keyType>::node():_key(), _parent(NULL), _left(NULL), _right(NULL) {}

template <typename keyType>
node<keyType>::node(const keyType initKey):_key(initKey), _parent(NULL), _left(NULL), _right(NULL){}

template <typename keyType>
node<keyType>::~node()
{
  delete _left;
  delete _right;
}

template <typename keyType>
void node<keyType>::setKey(const int& key)
{
  _key=key;
}

template <typename keyType>
int node<keyType>::getKey() const
{
  return _key;
}

template <typename keyType>
void node<keyType>::setParent(node<keyType>* parent)
{
  _parent=parent;
}

template <typename keyType>
node<keyType>* node<keyType>::getParent()const
{
  return _parent;
}

template <typename keyType>
void node<keyType>::setLeft(node<keyType>* left)
{
  _left=left;
}

template <typename keyType>
node<keyType>* node<keyType>::getLeft()const
{
  return _left;
}

template <typename keyType>
void node<keyType>::setRight(node<keyType>* right)
{
  _right=right;
}

template <typename keyType>
node<keyType>* node<keyType>::getRight()const
{
  return _right;
}
#endif // AVL_TREE_HH
