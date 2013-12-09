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

rb_node_t* rb_tree::rb_search_node(rb_node_t* root,rb_key_t key)
{
	if (root==PNIL)
	{
		return PNIL;
	} 
	else
	{
		rb_node_t* x=root;

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

rb_node_t* rb_tree::rb_rotate_left(rb_node_t* root,rb_node_t* x)
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
		root=y;
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

	return root;
}

rb_node_t* rb_tree::rb_rotate_right(rb_node_t* root,rb_node_t* y)
{
	rb_node_t* x = y->left;
	y->left=x->right;

	if (x->right != PNIL)
	{
		x->right->parent =y;
	}

	x->parent=y->parent;

	if (y->parent ==PNIL)
	{
		root=x;
	} 
	else if(y==y->parent->left)
	{
		y->parent->left = x;
	}
	else
	{
		y->parent->right = x;
	}

	x->right=y;
	y->parent=x;

	return root;
}

rb_node_t* rb_tree::rb_insert(rb_node_t* root,rb_key_t key)
{
	rb_node_t* z=rb_new_node(key);

	if (root==NULL || root==PNIL)
	{
		root=z;
		root->color=BLACK;

		cout<<" success!"<<endl;
		return root;
	} 
	else
	{
		rb_node_t* y=PNIL;
		rb_node_t* x=root;
		while (x!=PNIL)
		{
			y=x;
			if (z->key<x->key)
			{
				x=x->left;
			} 
			else if(z->key>x->key)
			{
				x=x->right;
			}
			else
			{
                cout<<" repeated, ignore!"<<endl;
				return root;
			}
		}

		z->parent=y;

		if (y==PNIL)
		{
			root=z;
		} 
		else if(z->key<y->key)
		{
			y->left=z;
		}
		else
		{
			y->right=z;
		}

        return rb_insert_fixup(root,z);
	}
}

rb_node_t* rb_tree::rb_insert_fixup(rb_node_t* root,rb_node_t* z)
{
	rb_node_t* y=PNIL;

	while (z->parent!=PNIL && z->parent->color==RED)
	{
        if (z->parent==z->parent->parent->left)
		{
	        y=z->parent->parent->right;		
            if (y->color==RED)//case1
			{
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;

				z=z->parent->parent;
			} 
			else 
			{
                if (z==z->parent->right)//case2
				{
					z=z->parent;
                    root=rb_rotate_left(root,z);
				} 
                z->parent->color=BLACK;//case3
				z->parent->parent->color=RED;
                root=rb_rotate_right(root,z->parent->parent);
			}
		} 
        else
		{
			y=z->parent->parent->left;		
            if (y->color==RED)//case4
			{
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;

                z=z->parent->parent;
			} 
			else 
			{
                if (z==z->parent->left)//case5
				{
					z=z->parent;
                    root=rb_rotate_right(root,z);
				} 
                z->parent->color=BLACK;//case6
				z->parent->parent->color=RED;
                root=rb_rotate_left(root,z->parent->parent);
			}
		}
	}
	root->color=BLACK;

	cout<<" success!"<<endl;
	return root;
}

rb_node_t* rb_tree::rb_tree_minimum(rb_node_t* x)
{
    while (x->left != PNIL)
    {
		x=x->left;
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
		while (y!=PNIL && x==y->right)
		{
			x=y;
			y=y->parent;
		}
		return y;
    }
}

int rb_tree::rb_tree_height(rb_node_t* root)
{
	int left_height,right_height;

    if (root==NULL || root==PNIL)
    {
	    return 0;
    }
	else
	{
        left_height=rb_tree_height(root->left);
        right_height=rb_tree_height(root->right);

        return (left_height>right_height?(left_height+1):(right_height+1));
	}
}

void rb_tree::inorder_tree_walk(rb_node_t* root)
{
    rb_node_t* x=root;
	if (x!=PNIL)
	{
		inorder_tree_walk(x->left);
		cout<<x->key<<" "<<x->color<<endl;
		inorder_tree_walk(x->right);
	}
}

void rb_tree::preorder_tree_walk(rb_node_t* root)
{
    rb_node_t* x=root;
	if (x!=PNIL)
	{
		cout<<x->key<<" "<<x->color<<endl;
		preorder_tree_walk(x->left);
		preorder_tree_walk(x->right);
	}
}

void rb_tree::postorder_tree_walk(rb_node_t* root)
{
    rb_node_t* x=root;
	if (x!=PNIL)
	{	
		postorder_tree_walk(x->left);
		postorder_tree_walk(x->right);
		cout<<x->key<<" "<<x->color<<endl;
	}
}

rb_node_t* rb_tree::rb_delete(rb_node_t* root,rb_key_t key)
{
     rb_node_t* z=rb_search_node(root,key);

	 if (z==PNIL)
	 {
		 cout<<" doesn't exist!"<<endl;
	 } 
	 else
	 {
         rb_node_t* y=PNIL;
         rb_node_t* x=PNIL;

	     if (z->left ==PNIL || z->right ==PNIL)
	     {
			 y =z;
	     } 
	     else
	     {
			 y=rb_tree_successor(z);
	     }

		 if (y->left != PNIL)
		 {
			 x=y->left;
		 } 
		 else
		 {
			 x=y->right;
		 }

	     x->parent=y->parent;

		 if (y->parent==PNIL)
		 {
			 root = x;
		 } 
		 else if (y == y->parent->left)
		 {
			 y->parent->left=x;
		 }
		 else
		 {
			 y->parent->right=x;
		 }

		 if (y!=z)
		 {
			 z->key=y->key;
		 }

		 if (y->color==BLACK)
		 { 
             root=rb_delete_fixup(root,x);
		 }

		 delete y;
		 cout<<" success!"<<endl;
	}
	return root;
}

rb_node_t* rb_tree::rb_delete_fixup(rb_node_t* root,rb_node_t* x)
{
	rb_node_t* uncle=PNIL;
	if (x->color==RED)
	{
        x->color=BLACK;
	} 
	else
	{
		while (x->color==BLACK && x!=root)
			{
				if (x==x->parent->left)
				{
		            uncle=x->parent->right;

                    if (uncle->color == RED)//case1
					{
						uncle->color = BLACK;
						x->parent->color = RED;
						root=rb_rotate_left(root,x->parent);
						uncle=x->parent->right;
					}
					else
					{
                        if (uncle->left->color==BLACK &&  uncle->right->color==BLACK)//case2
						{
                            uncle->color=RED;
							x=x->parent;
						} 
						else 
						{
                            if(uncle->right->color==BLACK)//case3
							{
								uncle->left->color=BLACK;
								uncle->color=RED;
								root=rb_rotate_right(root,uncle);
								uncle=x->parent->right;
							}
                            uncle->color=x->parent->color;//case4
							x->parent->color = BLACK;
							uncle->right->color = BLACK;
							root=rb_rotate_left(root,x->parent);
							x=root;
						}
					}
				} 
				else
				{
					uncle=x->parent->left;

                    if (uncle->color == RED)//case5
					{
						uncle->color = BLACK;
						x->parent->color = RED;
						root=rb_rotate_right(root,x->parent);
						uncle=x->parent->left;
					}
					else
					{
                        if (uncle->left->color==BLACK && uncle->right->color==BLACK)//case6
						{
                            uncle->color=RED;
							x=x->parent;
						} 
						else 
						{
                            if(uncle->left->color==BLACK)//case7
							{
								uncle->right->color=BLACK;
								uncle->color=RED;
								root=rb_rotate_left(root,uncle);
								uncle=x->parent->left;
							}
                            uncle->color=x->parent->color;//case8
							x->parent->color = BLACK;
							uncle->left->color = BLACK;
							root=rb_rotate_right(root,x->parent);
							x=root;
						}
					}
				}
			}
		}
	root->color=BLACK;
    return root;
}
