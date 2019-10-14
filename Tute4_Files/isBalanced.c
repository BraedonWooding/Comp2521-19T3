#include <stdio.h>
#include <stdlib.h>

#define TREE_IS_NOT_BALANCED (-99)

typedef struct bst_node_t {
    struct bst_node_t *left;
    struct bst_node_t *right;
    int value;
} *BSTree;

int isBalanced(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = isBalanced(t->left);
        int right = isBalanced(t->right);
        int diff;
        int height;
        if (left > right) {
            diff = left - right;
            height = left + 1;
        } else {
            diff = right - left;
            height = right + 1;
        }
        if (diff > 1) {
            return TREE_IS_NOT_BALANCED;
        }
        return height;
    }
}