#include <stddef.h>
#include <stdio.h>

typedef struct bst_t {
  struct bst_t *left;
  struct bst_t *right;
  int value;
} BSTree;

// Return height of tree and -1 if not balanced
int isBalanced(BSTree *tree) {
    if (tree == NULL) {
        return 0;
    }

    if (tree->left == NULL && tree->right == NULL) {
        return 1;
    }

    int left = isBalanced(tree->left);
    int right = isBalanced(tree->right);
    int diff;
    int height;
    if (left > right) {
        height = left + 1;
        diff = left - right;
    } else {
        height = right + 1;
        diff = right - left;
    }
    if (diff > 1) {
        return -1;
    } else {
        return height;
    }
}