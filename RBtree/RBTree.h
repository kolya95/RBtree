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
    rb_node_t* root_;
public:
    inline rb_node_t* getRoot() { return root_; }
    rb_tree() { root_ = 0; }

    rb_node_t* rb_new_node(rb_key_t key);      // создает новый с красным цветом

    rb_node_t* rb_search_node(rb_key_t key); // ищет по ключу

    void rb_rotate_left(rb_node_t* x); // правый поворот
    void rb_rotate_right(rb_node_t* y); // левый поворот

    void rb_insert(rb_key_t key); //вставка
    void rb_insert_fixup(rb_node_t* x);//восстановление балансировки


    void rb_delete(rb_key_t key);//удаление
    void rb_delete_fixup(rb_node_t* x);// восстанвление балансировки

    rb_node_t* rb_tree_successor(rb_node_t* x);
    rb_node_t* rb_tree_minimum(rb_node_t* x); // ищет самый левый

    int rb_tree_height(rb_node_t* root);

    void print(rb_node_t* w,int l);

};
#endif
