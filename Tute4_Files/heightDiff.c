#include <stdlib.h>
#include <stdio.h>

typedef struct bst_node_t {
    struct bst_node_t *left;
    struct bst_node_t *right;
    int value;
} *BSTree;

int printHeightDiff(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = printHeightDiff(t->left);
        int right = printHeightDiff(t->right);
        int diff;
        int height;
        if (left > right) {
            diff = left - right;
            height = left + 1;
        } else {
            diff = right - left;
            height = right + 1;
        }
        printf("%d diff: %d\n", t->value, diff);
        return height;
    }
}