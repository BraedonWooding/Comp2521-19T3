
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
  int result = 0;
  if (t == NULL) {
    return -1;
  } else if (t->value == key) {
    return 0;
  } else if (key < t->value) {
    result = BSTreeNodeDepth(t->left, key);
  } else {
    result = BSTreeNodeDepth(t->right, key);
  }

  if (result != -1) {
    result++;
  }
  return result;
}
