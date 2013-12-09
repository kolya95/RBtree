#include "RBTree.h"
#include <iostream>

using namespace std;

static rb_node_t NIL = {0, 0, 0, 0, BLACK};

#define PNIL (&NIL)

rb_node_t* rb_tree::rb_new_node(rb_key_t key)
{
  rb_node_t* node=new rb_node_t;

	node->key=key;
	node->left=PNIL;
	node->right=PNIL;
	node->parent=PNIL;
	node->color=RED;

    return node;
}

rb_node_t* rb_tree::rb_search_node(rb_key_t key)
{
    if (root_ == PNIL)
	{
		return PNIL;
	} 
	else
	{
        rb_node_t* x = root_;

		while (x!=PNIL)
		{
			if (key<x->key)
			{
				x=x->left;
			} 
			else if(key>x->key)
			{
				x=x->right;
			}
			else
			{
				return x; 
			}
		}
	}
	return PNIL;
}

void rb_tree::rb_rotate_left(rb_node_t* x)
{
    rb_node_t* y = x->right;
	x->right=y->left;

	if (y->left != PNIL)
	{
		y->left->parent =x;
	}

	y->parent=x->parent;

	if (x->parent ==PNIL)
	{
        root_ = y;
	} 
	else if(x==x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->left=x;
    x->parent=y;
}

void rb_tree::rb_rotate_right(rb_node_t* y)
{
    rb_node_t* x = y->left;
    y->left=x->right;

    if (x->right != PNIL)
	{
        x->right->parent = y;
	}

    x->parent = y->parent;

    if (y->parent == PNIL)
	{
        root_ = x;
	} 
	else if(y==y->parent->left)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}

    x->right = y;
    y->parent = x;

}

void rb_tree::rb_insert(rb_key_t key)
{
    rb_node_t* z = rb_new_node(key);

    if (root_ ==NULL || root_ ==PNIL)
	{
        root_ = z;
        root_->color = BLACK;

        cout<<"inserted"<<endl;
        return;
    }
	else
	{
        rb_node_t* y = PNIL;
        rb_node_t* x = root_;
		while (x!=PNIL)
		{
            y = x;
			if (z->key<x->key)
			{
                x = x->left;
			} 
			else if(z->key>x->key)
			{
                x = x->right;
			}
			else
			{
                cout<<"key repeated"<<endl;
                return;
			}
		}

        z->parent = y;

		if (y==PNIL)
		{
            root_ = z;
		} 
		else if(z->key<y->key)
		{
            y->left = z;
		}
		else
		{
            y->right = z;
		}

        rb_insert_fixup(z);
        return;
	}
}

void rb_tree::rb_insert_fixup(rb_node_t* z)
{
    rb_node_t* y = PNIL;

    while (z->parent != PNIL && z->parent->color == RED)
	{
        if (z->parent==z->parent->parent->left)
		{
            y = z->parent->parent->right;
            if (y->color == RED)//case1
			{
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
			} 
			else 
			{
                if (z == z->parent->right)//case2
				{
                    z = z->parent;
                    rb_rotate_left(z);
				} 
                z->parent->color = BLACK;//case3
                z->parent->parent->color = RED;
                rb_rotate_right(z->parent->parent);

			}
		} 
        else
		{
            y = z->parent->parent->left;
            if (y->color == RED)//case4
			{
                z->parent->color = BLACK;
                y->color = BLACK;
				z->parent->parent->color=RED;

                z = z->parent->parent;
			} 
			else 
			{
                if (z == z->parent->left)//case5
				{
                    z = z->parent;
                    rb_rotate_right(z);
                }
                z->parent->color = BLACK;//case6
                z->parent->parent->color = RED;
                rb_rotate_left(z->parent->parent);

			}
		}
	}
    root_->color = BLACK;
    return;
}

rb_node_t* rb_tree::rb_tree_minimum(rb_node_t* x)
{
    while (x->left != PNIL)
    {
        x = x->left;
    }
    return x;
}

rb_node_t* rb_tree::rb_tree_successor(rb_node_t* x)
{
    if (x->right != PNIL)
    {
		return rb_tree_minimum(x->right);
    } 
    else
    {
		rb_node_t* y=x->parent;
        while (y != PNIL && x == y->right)
		{
            x = y;
            y = y->parent;
		}
		return y;
    }
}

void rb_tree::rb_delete(rb_key_t key)
{
     rb_node_t* z=rb_search_node(key);

     if (z == PNIL)
	 {
         cout<<"key doesn't exist!"<<endl;
	 } 
	 else
	 {
         rb_node_t* y = PNIL;
         rb_node_t* x = PNIL;

         if (z->left == PNIL || z->right == PNIL)
	     {
			 y =z;
	     } 
	     else
	     {
             y = rb_tree_successor(z);
	     }

		 if (y->left != PNIL)
		 {
             x = y->left;
		 } 
		 else
		 {
             x = y->right;
		 }

         x->parent = y->parent;

         if (y->parent == PNIL)
		 {
             root_ = x;
		 } 
		 else if (y == y->parent->left)
		 {
             y->parent->left = x;
		 }
		 else
		 {
             y->parent->right = x;
		 }

		 if (y!=z)
		 {
             z->key = y->key;
		 }

         if (y->color == BLACK)
		 { 
             rb_delete_fixup(x);
		 }

		 delete y;
         cout<<"deleted"<<endl;
	}
    return;
}

void rb_tree::rb_delete_fixup(rb_node_t* x)
{
    rb_node_t* uncle = PNIL;
    if (x->color == RED)
    {
        x->color = BLACK;
	} 
	else
	{
        while (x->color == BLACK && x != root_)
			{
                if (x == x->parent->left)
				{
                    uncle = x->parent->right;

                    if (uncle->color == RED)//case1
					{
						uncle->color = BLACK;
						x->parent->color = RED;
                        rb_rotate_left(x->parent);
                        uncle = x->parent->right;
					}
					else
					{
                        if (uncle->left->color == BLACK &&  uncle->right->color == BLACK)//case2
						{
                            uncle->color = RED;
                            x = x->parent;
						} 
						else 
						{
                            if(uncle->right->color == BLACK)//case3
							{
                                uncle->left->color = BLACK;
                                uncle->color = RED;
                                rb_rotate_right(uncle);
                                uncle = x->parent->right;
							}
                            uncle->color = x->parent->color;//case4
							x->parent->color = BLACK;
							uncle->right->color = BLACK;
                            rb_rotate_left(x->parent);
                            x = root_;
						}
					}
				} 
				else
				{
                    uncle = x->parent->left;

                    if (uncle->color == RED)//case5
					{
						uncle->color = BLACK;
						x->parent->color = RED;
                        rb_rotate_right(x->parent);
                        uncle = x->parent->left;
					}
					else
					{
                        if (uncle->left->color == BLACK && uncle->right->color == BLACK)//case6
						{
                            uncle->color = RED;
                            x = x->parent;
						} 
						else 
						{
                            if(uncle->left->color == BLACK)//case7
							{
                                uncle->right->color = BLACK;
                                uncle->color = RED;
                                rb_rotate_left(uncle);
                                uncle = x->parent->left;
							}
                            uncle->color = x->parent->color;//case8
							x->parent->color = BLACK;
							uncle->left->color = BLACK;
                            rb_rotate_right(x->parent);
                            x = root_;
						}
					}
				}
			}
		}
    root_->color=BLACK;

    return;
}



void rb_tree::print (rb_node_t* w,int l)
{
  if (w!=NULL&&w!=PNIL)
  {
      print (w->right,l+1);
      for (int i = 0; i<l; i++)
          cout<<"  ";
      cout<<w->key;
      if(w->color == BLACK)
          cout<<'b'<<endl;
      else
          cout<<'r'<<endl;
      print (w->left,l+1);
  }
}

