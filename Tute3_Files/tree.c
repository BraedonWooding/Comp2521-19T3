#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode *BSTree;
typedef struct BSTNode {
  int value;
  BSTree left;
  BSTree right;
} BSTNode;

int maxBranchLen(BSTree t);
int nodeDepth(BSTree t, int key);
int countInternal(BSTree t);
BSTree insert(BSTree root, int wanted);
void print_prefix(BSTree root);

int main(int argc, char *argv[]) {
  BSTree root = NULL;
  for (int i = 1; i < argc; i++) {
    root = insert(root, atoi(argv[i]));
  }
  printf("For tree: ");
  print_prefix(root);
  putchar('\n');
  printf("\tMaxDepth/BranchLenn/Height = %d\n", maxBranchLen(root));
  printf("\tCountInternal              = %d\n", maxBranchLen(root));
}

void print_prefix(BSTree root) {
  if (root != NULL) {
    printf("%d ", root->value);
    print_prefix(root->left);
    print_prefix(root->right);
  }
}

BSTree insert(BSTree root, int wanted) {
  if (root == NULL) {
    // insert here
    root = malloc(sizeof *root);
    root->value = wanted;
    root->left = root->right = NULL;
  } else if (wanted < root->value) {
    root->left = insert(root->left, wanted);
  } else if (wanted > root->value) {
    root->right = insert(root->right, wanted);
  } // else don't insert duplicates!

  return root;
}

int maxBranchLen(BSTree t) {
  if (t == NULL) {
    return 0;
  } else {
    // The branch length will be our node
    // And the maximum path of our left and right
    int left = maxBranchLen(t->left);
    int right = maxBranchLen(t->right);
    if (left > right) {
      return left + 1;
    } else {
      return right + 1;
    }
  }
}

int nodeDepth(BSTree t, int key) {
  int depth;
  if (t == NULL) {
    return -1;
  } else if (key == t->value) {
    return 1;
  } else if (key < t->value) {
    depth = nodeDepth(t->left, key);
  } else {
    depth = nodeDepth(t->right, key);
  }
  if (depth != -1) {
    depth++;
  }
  return depth;
}

int countInternal(BSTree t) {
  if (t == NULL || (t->left == NULL && t->right == NULL)) {
    return 0;
  }
  return 1 + countInternal(t->left) + countInternal(t->right);
}
