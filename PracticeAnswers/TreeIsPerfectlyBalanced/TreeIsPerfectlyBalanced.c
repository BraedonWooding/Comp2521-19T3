
#include <stdlib.h>

#include "tree.h"

int size(Tree t) {
  if (t == NULL) {
    return 0;
  } else {
    int left = size(t->left);
    int right = size(t->right);
    return 1 + left + right;
  }
}

bool TreeIsPerfectlyBalanced(Tree t) {
  if (t == NULL) {
    return true;
  } else {
    int left = size(t->left);
    int right = size(t->right);
    if (left - right < -1 || left - right > 1) {
      return false;
    } else {
      return TreeIsPerfectlyBalanced(t->left) &&
             TreeIsPerfectlyBalanced(t->right);
    }
  }
}
