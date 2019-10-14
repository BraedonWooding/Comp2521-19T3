#include <stdlib.h>

typedef struct node *AVLNode;

struct node {
  AVLNode left;
  AVLNode right;
  int key;
  // Could we also store height?
  // Yes -- it would make it faster
  // But we won't since its easy to get
};

int height(AVLNode n) {
  if (n == NULL) {
    return 0;
  } else {
    int left = height(n->left);
    int right = height(n->right);
    return (left > right ? left : right) + 1;
  }
}

/*
  Right Rotating at 7
     7
    / \
   3   8
  / \
 2   5
 
 1)
   3
  / \
 2   7
    / \
   3   8
  / \
 2   5
 
 2)
   3
  / \
 2   7
    / \
   5   8
*/
AVLNode right_rotate(AVLNode root) {
  AVLNode left = root->left;
  AVLNode left_right = left->right;
  left->right = root;             // 1)
  root->left = left_right;        // 2)
  return left;
}

/*
  Left Rotating at 3
   3
  / \
 2   7
    / \
   5   8
 
 1)
    7
   / \
  3   8
 / \
2   7
   / \
  5   8
 
 2)
     7
    / \
   3   8
  / \
 2   5
*/
AVLNode left_rotate(AVLNode root) {
  AVLNode right = root->right;
  AVLNode right_left = right->left;
  right->left = root;             // 1)
  root->right = right_left;       // 2)
  return right;
}

AVLNode insert(AVLNode root, int key) {
  // Case 1) Empty Tree
  if (root == NULL) {
    root = malloc(sizeof(*root));
    root->left = root->right = NULL;
    root->key = key;
    return root;
  }
  
  // Case 2) Duplicates
  if (root->key == key) {
    return root;
  } else if (key < root->key) /* Case 3) Left */ {
    root->left = insert(root->left, key);
  } else /* Case 4) Right */ {
    root->right = insert(root->right, key);
  }
  
  // What happens if we do height(root->right) - height(root->left)
  int balance = height(root->left) - height(root->right);
  if (balance > 1) {
    // Unbalanced in left
    // What way do we rotate??
    // Which one do we need to double rotate?
    if (key < root->left->key) {
    
    } else {
      // key > root->left->key;
    }
  } else if (balance < -1) {
    // Unbalanced in right
    // What way do we rotate??
    // Which one do we need to double rotate?
    if (key > root->right->key) {
    
    } else {
      // key < root->right->key
    }
  }
  
  return root;
}