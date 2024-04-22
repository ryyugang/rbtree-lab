#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void rbtree_to_print(node_t *t, node_t *nil);

int main(int argc, char *argv[])
{
    const key_t arr[] = {10, 5, 8, 34, 67, 23, 156, 24, 2, 12, 24, 36, 990, 25};
    const size_t n = sizeof(arr) / sizeof(arr[0]);
    rbtree *t = new_rbtree();
    for (int i = 0; i < n; i ++) {
        rbtree_insert(t, arr[i]);
    }
    rbtree_to_print(t->root, t->nil);
    return 0;

    // rbtree *t = new_rbtree();
    // for (int i = 1; i <= 15; i ++) {
    //     rbtree_insert(t, i);
    // }
    // rbtree_to_print(t->root, t->nil);
    // return 0;
}