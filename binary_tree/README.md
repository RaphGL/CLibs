# Binary Tree

A generic binary tree

## Usage

Create binary tree

```c
bt_BinaryTree *bt = bt_new((char*)'a');
```

Delete binary tree

```c
bt_remove_node(bt);
```

Insert to the right leaf

```c
bt_insert_right(bt, (char*)'b');
```

Insert to the left leaf

```c
bt_insert_right(bt, (char*)'c');
```

Insert in the right leaf's left leaf

```c
bt_insert_left(bt->right, (char*)'d');
```

Remove leaf and all its children

```c
bt_remove_node(bt->right);
```

Get item from leaf

```c
char = *(char*)bt_getitem(bt.left);
```

Print tree

```c
bt_print(bt, "%c");
```

