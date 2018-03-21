#include<iostream>
#include "node.hh"
#include "AVL_tree.hh"
#include <cstdlib>
using namespace std;

template<typename T>
bool menu(AVL_tree<T>& t)
{
  char wybor;
  cin >> wybor;

  switch(wybor)
    {
      case 'd':
        {
          T temp;
          cout<<"Wpisz element do dodania.\n";
          cin >> temp;
          t.insertAVLNode(temp);
          return true;
        }
      case 'u':
        {
          T temp;
          cout<<"Wpisz element do usunięcia\n";
          cin >> temp;
          t.deleteAVLNode(temp);
          return true;
        }
      case 'p':
        {
          t.preorder(t.getRoot());
          return true;
        }
      case 'i':
        {
          t.inorder(t.getRoot());
          return true;
        }
      case 'z':
        {
         t.postorder(t.getRoot());
         return true;
        }
      case 'h':
        {
         cout << t.height(t.getRoot()) << endl;
         return true;
        }
      case 'r':
        {
         if(t.getRoot()!=NULL)
           t.getRoot()->print();  
         else
             cout << "nic nie ma";
         cout << endl;
         return true;
        }
      default:
        return false;
    }
}

int main()
{

AVL_tree<int> t;

cout << "Wpisz:\nd-aby dodac element\nu-aby usunac element\np-preorder\n";
cout <<  "i-inorder\nz-postorder\nh-wyswietlic wyskoskosc drzewa\nr-zobaczyc co jest w korzeniu \ncokolwiek innego zamyka program\n";
while(menu<int>(t));

return 0;
}

