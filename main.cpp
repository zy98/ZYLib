#include "Other/Test.h"
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;
using namespace ZYLib;




int main()
{
    BTree<int> lt;
    BTree<int> rt;
    lt.insert(1,NULL);
    BTreeNode<int>* node=lt.find(1);
    lt.insert(2,node);
    lt.insert(3,node);
    node=lt.find(2);
    lt.insert(4,node);
    lt.insert(5,node);
    node=lt.find(3);
    lt.insert(6,node);
    lt.insert(7,node);
    node=lt.find(4);
    lt.insert(8,node);
    lt.insert(9,node);
    node=lt.find(5);
    lt.insert(10,node);

    rt.insert(0,NULL);
    node=rt.find(0);
    rt.insert(6,node);
    rt.insert(2,node);
    node=rt.find(2);
    rt.insert(7,node);
    rt.insert(8,node);

    SharedPointer<BTree<int> > ret=lt+rt;

    BTreeNode<int>* tail=NULL;
    BTreeNode<int>* head=lt.thread(PreOrder,tail);

    while(head != NULL)
    {
        cout<<head->value<<" ";
        head=head->right;
    }
    cout<<endl;

    while(tail != NULL)
    {
        cout<<tail->value<<" ";
        tail=tail->left;
    }
    cout<<endl;

    for(rt.begin();!rt.end();rt.next())
        cout<<rt.current()<<" ";
    cout<<endl;



    SharedPointer<Array<int> > level=ret->traversal(LevelOrder);

    for(int i=0;i<level->length();i++)
    {
        cout<<(*level)[i]<<" ";
    }

    cout<<endl;

}
