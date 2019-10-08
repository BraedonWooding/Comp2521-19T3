#include <stddef.h>
#include <stdio.h>

typedef struct bst_t {
  struct bst_t *left;
  struct bst_t *right;
  int value;
} BSTree;

int printHeightDiff(BSTree *tree) {
  if (tree == NULL) {
    return 0;
  }

  if (tree->left == NULL && tree->right == NULL) {
    return 1;
  }

  int left = printHeightDiff(tree->left);
  int right = printHeightDiff(tree->right);
  int diff;
  int height;
  if (left > right) {
    diff = left - right;
    height = left + 1;
  } else {
    diff = right - left;
    height = right + 1;
  }
  printf("%d has diff %d\n", tree->value, diff);
  return height;
}
