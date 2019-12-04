
#include <stdlib.h>

#include "BSTree.h"

// I've attached a simpler way of doing this question at the bottom

// Helper function to carry some state along with us
// Not pure recursion but useful.
// We set state to -1 when we find the value we want
int BSTreeGetKthRec(BSTree t, int k, int *state) {
  if (t == NULL) {
    return 0;
  }

  int left = BSTreeGetKthRec(t->left, k, state);
  if (*state == -1) {
    // If found in left subtree
    return left;
  }

  // Else we are the next smallest
  // If we are the next smallest that we want
  // Then set state to -1 and return
  // Else find the next smallest after us
  if (k == *state) {
    *state = -1;
    return t->value;
  } else {
    (*state)++;
  }

  // Return right regardless since we only propagate
  // it if state == -1
  int right = BSTreeGetKthRec(t->right, k, state);
  return right;
}

int BSTreeGetKth(BSTree t, int k) {
  // There are many ways to solve this problem.
  // This is just one that uses a stack (recursion)
  int state = 0; // find the 0'th smallest
  return BSTreeGetKthRec(t, k, &state);
}

/*
  Simpler way.
*/

int SimplerBSTreeGetKth(BSTree t, int k) {
	int leftSize = BSTreeSize(t->left);
	if (k == leftSize) {
		return t->value;
	} else if (k < leftSize) {
		return BSTreeGetKth(t->left, k);
	} else {
		return BSTreeGetKth(t->right, k - leftSize - 1);
	}
}

static int BSTreeSize(BSTree t) {
	if (t == NULL) {
		return 0;
	} else {
		return 1 + BSTreeSize(t->left) + BSTreeSize(t->right);
	}
}

