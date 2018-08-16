#include "Other/Test.h"
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;
using namespace ZYLib;




int main()
{
    char* s="KLFGMIJ";
    clock_t begin=clock();

    GTree<char> tree;
    tree.insert('A',NULL);

    cout<<1<<endl;
    GTreeNode<char>* node=tree.find('A');
    cout<<node<<endl;
    tree.insert('B',node);
    tree.insert('C',node);
    tree.insert('D',node);
    cout<<s<<endl;

    node=tree.find('B');
    tree.insert('E',node);
    tree.insert('F',node);
    node=tree.find('E');
    tree.insert('K',node);
    tree.insert('L',node);
    node=tree.find('C');
    tree.insert('G',node);

    node=tree.find('D');
    tree.insert('H',node);
    tree.insert('I',node);
    tree.insert('J',node);
    node=tree.find('H');
    tree.insert('M',node);




    for(int i=0;i<7;i++)
    {
        AbsTreeNode<char>* node=tree.find(s[i]);
        while(node != NULL)
        {
            cout<<node->m_value<<" ";
            node=(node->m_parent);
        }
        cout<<endl;
    }

    clock_t end=clock();



    cout<<end-begin<<endl;

}
