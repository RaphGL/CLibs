#ifndef BINTREE_H
#define BINTREE_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct bintree {
  void *val;
  struct bintree *left;
  struct bintree *right;
} bt_BinaryTree;

bt_BinaryTree *bt_new(void *val);
void *bt_getitem(bt_BinaryTree *bt);
bool bt_insert_right(bt_BinaryTree *bt, void *val);
bool bt_insert_left(bt_BinaryTree *bt, void *val);
void bt_print(const bt_BinaryTree *bt, char *fmt);
bool bt_remove_node(bt_BinaryTree *bt);
size_t bt_sizeof(bt_BinaryTree *bt);
bt_BinaryTree *bt_find(bt_BinaryTree *bt, void *val);

#endif
