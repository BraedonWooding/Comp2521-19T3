
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
  if (t == NULL) {
    return 0;
  } else {
    int result = TreeSumOdds(t->left) + TreeSumOdds(t->right);
    if (t->value % 2 != 0) {
      result += t->value;
    }
    return result;
  }
}
