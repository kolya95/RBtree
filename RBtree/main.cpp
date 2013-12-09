#include <iostream>
#include <ctime>
#include "RBTree.h"

using namespace std;

int main()
{
    int count = 10;
    rb_tree a;
    int key;

    for (int i = 0; i < count; ++i)
    {
        cin>>key;
        a.rb_insert(key);
        a.print(a.getRoot(),1);
    }
    for (int i = 0;i<count;i++)
    {
        cin>>key;
        a.rb_delete(key);
        a.print(a.getRoot(),1);
    }
    return 0;
}
