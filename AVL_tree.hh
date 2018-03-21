#ifndef AVL_TREE_HH
#define AVL_TREE_HH


#include <iostream>
#include "node.hh"
#include <algorithm>
/*
Class template representing AVL self balancing BST.
*/
template <typename treeType>
class AVL_tree
{
  private:
   node<treeType>* _root;//Root of the tree
   //Takes a root of a tree or a subtree, and returns diffrence in height between left 
   //and right child
   int  balanceFactor(const node<treeType>*const&) const;
   //Performs left rotation on given node
   node<treeType>* lRotate(node<treeType>*);
   //Performs left rotation, then right rotation on given node
   node<treeType>* lrRotate(node<treeType>*);
   //Perfornms right rotation, then left rotation on given node
   node<treeType>* rlRotate(node<treeType>*);
   //Performs right rotation on given node
   node<treeType>* rRotate(node<treeType>*);
   //Rebalances thee tree starting from given node
   void            rebalance(node<treeType>*);
  public:
   AVL_tree():_root(NULL){};//Sets _root to NULL
   ~AVL_tree();//Calls node destructor on _root
   node<treeType>* getRoot()                        const;//Returns _root
   //Takes a root of a tree or a subtree, and returns it's height 
   int   height(const node<treeType>*const&)        const;
   void  preorder(const node<treeType>*const&)      const;//Performs preorder traversal
   void  inorder(const node<treeType>*const&)       const;//Performs inorder traversal
   void  postorder(const node<treeType>*const&)     const;//Performs posorder traversal
   bool  insertAVLNode(const treeType&);//Adds new data to the tree
   void  deleteAVLNode(const treeType&);//Deletes data from the trrr
};

template <typename treeType>
AVL_tree<treeType>::~AVL_tree()
{
  delete _root;
}

template <typename treeType>
int AVL_tree<treeType>::height(const node<treeType>*const& root) const
{
 if(root==NULL)
   return -1;
 return 1+std::max(height(root->getLeft()),height(root->getRight()));
}

template <typename treeType>
int AVL_tree<treeType>::balanceFactor(const node<treeType>*const& root) const
{
 int lHeight=height(root->getLeft());
 int rHeight=height(root->getRight());
 int balance=rHeight-lHeight;
 return balance;

}

template <typename treeType>
node<treeType>* AVL_tree<treeType>::lRotate(node<treeType>* root)
{
  node<treeType>* temp=root->getRight();
  temp->setParent(root->getParent());
  root->setRight(temp->getLeft());
 
  if(root->getRight() != NULL)
   root->getRight()->setParent(root);

  temp->setLeft(root);
  root->setParent(temp);

  if(temp->getParent() != NULL)
    {
      if(temp->getParent()->getRight() == root)
        temp->getParent()->setRight(temp);
      else
        temp->getParent()->setLeft(temp); 
    } 

 return temp;
}


template <typename treeType>
node<treeType>* AVL_tree<treeType>::lrRotate(node<treeType>* root)
{
  root->setLeft(lRotate(root->getLeft()));
  return rRotate(root);
}

template <typename treeType>
node<treeType>* AVL_tree<treeType>::rlRotate(node<treeType>* root)
{
  root->setRight(rRotate(root->getRight()));
  return lRotate(root);
}


template <typename treeType>
node<treeType>* AVL_tree<treeType>::rRotate(node<treeType>* root)
{
  node<treeType>* temp=root->getLeft();
  temp->setParent(root->getParent());
  root->setLeft(temp->getRight());

  if(root->getLeft() != NULL)
    root->getLeft()->setParent(root);

  temp->setRight(root);
  root->setParent(temp);

  if(temp->getParent() != NULL)
    {
      if(temp->getParent()->getRight() == root)
        temp->getParent()->setRight(temp);
      else
        temp->getParent()->setLeft(temp); 
    } 
  
  return temp;
}

template <typename treeType>
void AVL_tree<treeType>::rebalance(node<treeType>* temp)
{
  int bFactor=balanceFactor(temp);

   if (bFactor == -2)
      {
       if (height(temp->getLeft()->getLeft()) >= height(temp->getLeft()->getRight()))
           temp = rRotate(temp);
       else
           temp = lrRotate(temp);
      }
   else if (bFactor == 2)
     {
       if (height(temp->getRight()->getRight()) >= height(temp->getRight()->getLeft()))
           temp = lRotate(temp);
       else
           temp = rlRotate(temp);  
     }

  if(temp->getParent() != NULL)
    rebalance(temp->getParent());
  else
    _root=temp;
}


template <typename treeType>
bool AVL_tree<treeType>::insertAVLNode(const treeType& key)
{

 if(_root==NULL)
   _root=new node<treeType>(key);
 else
  {
    node<treeType>* temp=_root;
    node<treeType>* parent;
   
    while(true)
      {
        if(temp->getKey()==key)
          return false;
        
        parent=temp;


        bool goLeft=temp->getKey()>key;
        temp=goLeft?temp->getLeft():temp->getRight();
        
        if(temp==NULL)
          {
            if(goLeft)
	      {
                parent->setLeft(new node<treeType>(key));
                parent->getLeft()->setParent(parent);
              }
            else
              {
                parent->setRight(new node<treeType>(key));
                parent->getRight()->setParent(parent);
              }
           rebalance(parent);
            break;  
          }
      }

   }
return true;
}

template <typename treeType>
void AVL_tree<treeType>::deleteAVLNode(const treeType& delKey)
{
 if(_root == NULL)
   return;
 
 node<treeType>
   *temp    = _root,
   *parent  = NULL,
   *delNode = NULL,
   *child   = _root;
             
 while (child != NULL)
   {
     parent = temp;
     temp = child;
     child = delKey >= temp->getKey() ? temp->getRight() : temp->getLeft();
     if(delKey == temp->getKey())
       delNode = temp;
   }
                 
  if(delNode != NULL)
    {
      delNode->setKey(temp->getKey());
                               
      child = temp->getLeft() != NULL ? temp->getLeft() : temp->getRight();
                                         
      if(_root->getKey() == delKey)
        {
          node<treeType>* a=_root;
          _root = child;
          a->setLeft(NULL);
          a->setRight(NULL);
          delete a;        
        }
      else
        {
          if(parent->getLeft() == temp)
            {
              parent->setLeft(child); 
              temp->setLeft(NULL);
              temp->setRight(NULL);
              delete temp;        
            }
          else
            {
              parent->setRight(child);
              temp->setLeft(NULL);
              temp->setRight(NULL);
              delete temp;        
            }
                                                                                     
          rebalance(parent);
        }
    }
}

template <typename treeType>
void AVL_tree<treeType>::preorder(const node<treeType>*const& root) const
{
 if(root==NULL)
  return;
     root->print();
     preorder(root->getLeft());
     preorder(root->getRight());

}

template <typename treeType>
void AVL_tree<treeType>::inorder(const node<treeType>*const& root) const 
{
 if(root==NULL)
   return;
     preorder(root->getLeft());
     root->print();
     preorder(root->getRight());

}

template <typename treeType>
void AVL_tree<treeType>::postorder(const node<treeType>*const& root) const
{
 if(root==NULL)
   return;
     preorder(root->getLeft());
     preorder(root->getRight());
     root->print();

}

template<typename treeType>
node<treeType>* AVL_tree<treeType>::getRoot() const
{
  return _root;
}
#endif // AVL_TREE_HH
