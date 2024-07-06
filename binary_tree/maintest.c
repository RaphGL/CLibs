#include <assert.h>
#include "bintree.h"
#include <stdio.h>

int main(void)
{
    bt_BinaryTree *bt = bt_new((char*)'a');
    assert(*(char*)bt_getitem(bt) == 'a');

    bt_insert_right(bt, (char*)'b');
    assert(*(char*)bt_getitem(bt->right) == 'b');

    bt_insert_left(bt, (char*)'c');
    assert(*(char*)bt_getitem(bt->left) == 'c');
    assert(bt_sizeof(bt) == 3);

    bt_insert_right(bt->right, (char*)'z');
    bt_insert_left(bt->right, (char*)'y');
    assert(bt_find(bt, (char*)'z') == bt->right->right);

    bt_print(bt, "%c");
    bt_remove_node(bt);
    puts("Passed all tests");
    return 0;
}
