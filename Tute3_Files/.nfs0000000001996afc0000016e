#include <stddef.h>
#include <stdio.h>

typedef struct bst_t {
  struct bst_t *left;
  struct bst_t *right;
  int value;
} BSTree;

int width(BSTree *tree) {
    if (tree == NULL) {
        return 0;
    }

    if (tree->left == NULL && tree->right == NULL) {
        return 3;
    }

    int left = width(tree->left);
    int right = width(tree->right);
    return left + right + 3;
}