#include <stdlib.h>

typedef struct bst_node_t {
    struct bst_node_t *left;
    struct bst_node_t *right;
    int value;
} *BSTree;

int numNodes(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = numNodes(t->left);
        int right = numNodes(t->right);
        return left + right + 1;
    }
}

int widthNumNodes(BSTree t) {
    return numNodes(t) * 3;
}

int width(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = width(t->left);
        int right = width(t->right);
        return left + right + 3;
    }
}