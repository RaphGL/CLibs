#ifndef BINTREE_H
#define BINTREE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct bintree {
  int val;
  struct bintree *left;
  struct bintree *right;
} bt_BinaryTree;

typedef enum bterrors {
  BT_NODE_EXISTS,
  BT_SUCCESS,
  BT_NODE_DOES_NOT_EXIST
} bterr_t;

/*
 * Allocates space for a new node and assigns a value to it
 *
 * @param val The value stored in the node
 *
 * @return A newly allocated binary tree node or NULL if it fails
 */
bt_BinaryTree *bt_new(int val) {
  bt_BinaryTree *new = malloc(sizeof(bt_BinaryTree));
  if (new == NULL) {
    return NULL;
  }
  new->left = NULL;
  new->right = NULL;
  new->val = val;
  return new;
}

/*
 * Inserts a new node on the right
 *
 * @param bt The node that will be inserted into
 * @param val The value of the new node
 *
 * @return BT_NODE_EXISTS or BT_SUCCESS
 */
bterr_t bt_insert_right(bt_BinaryTree *bt, int val) {
  bt_BinaryTree *tmp = bt;
  if (tmp->right == NULL) {
    tmp->right = bt_new(val);
  } else {
    return BT_NODE_EXISTS;
  }
  return BT_SUCCESS;
}

/*
 * Inserts a new node on the left
 *
 * @param bt The node that will be inserted into
 * @param val The value of the new node
 *
 * @return BT_NODE_EXISTS or BT_SUCCESS
 */
bterr_t bt_insert_left(bt_BinaryTree *bt, int val) {
  bt_BinaryTree *tmp = bt;
  if (tmp->left == NULL) {
    tmp->left = bt_new(val);
  } else {
    return BT_NODE_EXISTS;
  }
  return BT_SUCCESS;
}

/*
 * Prints the current node's value
 *
 * @param bt The node that will be printed
 * @param depth The node's depth in the tree
 *
 * @return BT_NODE_DOES_NOT_EXIST or BT_SUCCESS
 */
bterr_t bt_print_node(bt_BinaryTree *bt, int depth) {
  if (bt == NULL) {
    return BT_NODE_DOES_NOT_EXIST;
  }
  for (int i = 0; i <= depth; i++) {
    printf(" ");
  }
  printf("%d\n", bt->val);
  return BT_SUCCESS;
}

/*
 * Removes a node and all of it's children
 *
 * @param bt The node that will be removed
 *
 * @return BT_NODE_DOES_NOT_EXIST or BT_SUCCESS
 */
bterr_t bt_remove_node(bt_BinaryTree *bt) {
  if (bt == NULL) {
    return BT_NODE_DOES_NOT_EXIST;
  }
  bt_remove_node(bt->left);
  bt_remove_node(bt->right);
  free(bt);
  return BT_SUCCESS;
}

/*
 * Total size of the binary tree
 *
 * @param bt Binary tree's root node
 *
 * @return Number of nodes in the binary tree
 */
size_t bt_sizeof(bt_BinaryTree *bt) {
  if (bt == NULL) {
    return 0;
  }
  return bt_sizeof(bt->left) + 1 + bt_sizeof(bt->right);
}

/*
 * Find a value in the binary tree
 *
 * @param bt Binary tree's root
 * @param val Value that's being searched for
 *
 * @return The node containing the searched value
 */
bt_BinaryTree *bt_find(bt_BinaryTree *bt, int val) {
  bt_BinaryTree *tmp;

  if (!bt) {
    tmp = NULL;
  } else if (bt->val == val) {
    tmp = bt;
  }
  if (bt->left != NULL)
    tmp = bt_find(bt->left, val);
  if (bt->right != NULL)
    tmp = bt_find(bt->right, val);
  return tmp;
}
#endif
