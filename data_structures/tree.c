#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <stdio.h>

typedef struct treenode
{
  int data;
  struct treenode *left;
  struct treenode *right;
} TreeNode;

TreeNode *tree_new(int data);
int tree_insert(TreeNode *root, TreeNode *node);
void tree_remove(TreeNode *root, int data);
int tree_find(TreeNode *root, int data);
void tree_print(TreeNode *root);

int main(void)
{
  TreeNode *root = tree_new(0);
  tree_insert(root, tree_new(-2));
  tree_insert(root, tree_new(-1));
  tree_insert(root, tree_new(-3));
  tree_insert(root, tree_new(6));
  tree_insert(root, tree_new(3));
  tree_insert(root, tree_new(9));
  tree_remove(root, 6);
  return 0;
}

TreeNode *tree_new(int data)
{
  TreeNode *tmp = malloc(sizeof(TreeNode));
  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;
  return tmp;
}

// returns 0 if inserted, 1 if already in tree
int tree_insert(TreeNode *root, TreeNode *node)
{
  TreeNode *curr_node = root;
  for (;;)
  {
    if (node->data < curr_node->data && curr_node->left != NULL)
    {
      curr_node = curr_node->left;
    }
    else if (node->data > curr_node->data && curr_node->right != NULL)
    {
      curr_node = curr_node->right;
    }
    else
    {
      if (node->data < curr_node->data)
      {
        curr_node->left = node;
        return 0;
      }
      else if (node->data > curr_node->data)
      {
        curr_node->right = node;
        return 0;
      }

      return 1;
    }
  }
}

void tree_remove(TreeNode *root, int data)
{
  TreeNode *prev_node = NULL;
  TreeNode *curr_node = root;
  enum last_path
  {
    LEFT,
    RIGHT
  };

  enum last_path chosen;
  for (;;)
  {
    if (data < curr_node->data)
    {
      prev_node = curr_node;
      curr_node = curr_node->left;
      chosen = LEFT;
    }
    else if (data > curr_node->data)
    {
      prev_node = curr_node;
      curr_node = curr_node->right;
      chosen = RIGHT;
    }
    else if (data == curr_node->data)
    {
      if (chosen == LEFT)
      {
        prev_node->left = NULL;
      }
      else if (chosen == RIGHT)
      {
        prev_node->right = NULL;
      }
      tree_insert(root, curr_node->left);
      tree_insert(root, curr_node->right);
      free(curr_node);
      return;
    }
  }
}
#endif