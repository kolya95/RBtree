#ifndef  _RBTREE_H_
#define  _RBTREE_H_

//#define NULL    0

typedef int rb_key_t;

enum rb_color_t
{
    RED = 0,
    BLACK = 1
};

struct rb_node_t 
{
	rb_node_t *left,*right,*parent;
    rb_key_t key;
    rb_color_t color;
};
class rb_tree
{
private:

public:
    rb_node_t* root_;
    rb_tree() { root_ = 0; }

    rb_node_t* rb_new_node(rb_key_t key);

    rb_node_t* rb_search_node(rb_node_t* root,rb_key_t key);

    rb_node_t* rb_rotate_left(rb_node_t* root,rb_node_t* x);
    rb_node_t* rb_rotate_right(rb_node_t* root,rb_node_t* y);

    rb_node_t* rb_insert(rb_node_t* root,rb_key_t key);
    rb_node_t* rb_insert_fixup(rb_node_t* root,rb_node_t* x);

    rb_node_t* rb_tree_successor(rb_node_t* x);
    rb_node_t* rb_tree_minimum(rb_node_t* x);

    int rb_tree_height(rb_node_t* root);

    void inorder_tree_walk(rb_node_t* root);
    void preorder_tree_walk(rb_node_t* root);
    void postorder_tree_walk(rb_node_t* root);

    rb_node_t* rb_delete(rb_node_t* root,rb_key_t key);
    rb_node_t* rb_delete_fixup(rb_node_t* root,rb_node_t* x);
};
#endif
