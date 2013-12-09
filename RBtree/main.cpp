#include <iostream>
#include <ctime>
#include "RBTree.h"

using namespace std;

int main()
{
  int i, count = 9;
    rb_tree a;
    int key;
    /*srand(time(0));*/
    for (i = 1; i <= count; ++i)
    {
        /*key = rand() % count;*/
        cin>>key;

        cout<<i<<" insert key "<<key;
        a.rb_insert(key);
    }

    /*cout<<"Tree height: "<<rb_tree_height(root)<<endl;

    preorder_tree_walk(root);
    cout<<endl;
    inorder_tree_walk(root);
    cout<<endl;*/

    for (i=1;i<=count;i++)
    {
        cin>>key;

        cout<<i<<" delete key "<<key;
        a.rb_delete(key);
    }

    return 0;
}
