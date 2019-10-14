# Week 05

## Splay Trees

There are many versions of this out there.

I feel this is the easiest to understand.

```c
#include <stdlib.h>

typedef struct node *SplayNode;

struct node {
  SplayNode left;
  SplayNode right;
  int key;
};

/*
  For example if we have:
      7
     / \
    /   \
   3     9
  / \   / \
 2   5 8  10

 A left rotation on '7' will be
 1)
     7
    / \
   3    8
  / \
 2   5
 
 right = 9
        / \
       8  10
       
 2)
       9
      / \
     7  10
    / \
   3   8
  / \
 2   5
*/
SplayNode left_rotate(SplayNode node) {
  SplayNode right = node->right;
  node->right = right->left;  // 1)
  right->left = node;         // 2)
  return right;
}

/*
  For example if we have:
      7
     / \
    /   \
   3     9
  / \   / \
 2   5 8  10

 A right rotation on '7' will be
 1)
     7
    / \
   5   9
      / \
     8  10

 left  = 3
        / \
       2   5

 2)
       3
      / \
     2   7
        / \
       5   9
          / \
         8  10
*/
SplayNode right_rotate(SplayNode node) {
  SplayNode left = node->left;
  node->left = left->right;    // 1)
  left->right = node;          // 2)
  return left;
}

/*
  Bring the node that holds key to the top and return the new root.
  If the key doesn't exist then just do nothing (i.e. return root)
*/
SplayNode splay(SplayNode root, int key) {
  // TODO: I'll just give some cases
  
  // Case 1) Empty tree
  if (root == NULL) {
    
  }
  
  // Case 2) The root node is key
  if (root->key == key) {
  
  }
  
  // Case 3) Key Lies in left subtree
  if (root->key > key) {
    // Case 3) a) Key Not in tree
    if (root->left == NULL) {
    }
    
    // Case 3) b) Zig Zig (i.e. Left Left)
    // Left Left means that our wanted node
    // is in our left -> left subtree

    // What do we do?  How many rotations
    // What do we want to do beforehand
    if (key < root->left->key) {
      // Lies in left -> left
    } else if (key > root->left->key) /* Case 3) c) Zig Zag i.e. Left Right */ {
      // Lies in left -> right    
    }
    
    // What do we do now to make it so that our new root is our left child
    // Remember that we may not find our left child (meaning our left may be NULL)
  } else /* Case 4) Lies in Right subtree */ {
  
    // Case 4) a) Key Not in tree
    if (root->right == NULL) {
    }
    
    // Case 4) b) Zag Zig (i.e. Right Left)
    // What do we do?  How many rotations
    // What do we want to do beforehand
    if (key < root->right->key) {
      // lies in right -> left
    } else if (key > root->right->key) /* Case 4) c) Zig Zag i.e. Right Right */ {
      // lies in right -> right
    }
    
    // What do we do now to make it so that our new root is our right child
    // Remember that we may not find our right child (meaning our right may be NULL)
  }
}

// Returns new root  
SplayNode insert(SplayNode root, int key) {
  // Iterative method since its a little cleaner in this specific case
  SplayNode cur = root;
  SplayNode prev = NULL;
  while (cur) {
    prev = cur;
    if (key > cur->key) {
      cur = cur->right;
    } else if (key < cur->key) {
      cur = cur->left;
    } else {
      // MOST websites get this wrong!!
      // Even wikipedia!!
      // We want to have no duplicates
      // So we have to check for ==
      // Why can't we just do return root??
      // What are they expecting to be root
      return splay(root, key);
    }
  }
  
  SplayNode new = malloc(sizeof(*new));
  new->left = new->right = NULL;
  new->key = key;
  
  if (prev == NULL) {
    // empty tree
    root = new;
  } else if (key < prev->key) {
    // in left subtree
    prev->left = new;
  } else {
    prev->right = new;
  }  
  return splay(root, key);
}

// Splays the tree for the given key
// If the returned node doesn't contain key
// Then the key wasn't found.
SplayNode search(SplayNode root, int key) {
  return splay(root, key);
}
```

## Example

Given the insertion order `5 3 8 7 4` how will the tree look at each stage?

Let `t` be the answer to the above question, what will the tree look like after each of the following;

- `search(t, 7)`
- `search(t, 8)`
- `search(t, 6)`

## AVL Trees

!> IMPORTANT: In previous exams they have asked questions that require you to know that AVL trees have to be balanced, what denotes that a tree is an AVL tree and thus is balanced?

```c
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
```

?> Why isn't this O(log n) for insertion and what could we do to fix that

### Example

?> `12 10 8 6 4 2` what is the resultant tree


## 2-3-4 Trees

We aren't going to implement one because of the following

1) Red Black trees are isomorphic to 2-3-4 Trees (for each 2-3-4 tree there is an identical red black) and are much easier to implement
2) There are a ridiculous amount of edge cases
3) Timing is rough

?> Insert `1 2 3 4 5 8 6 7 9 10` into a 2-3-4

?> What are the search costs for `1 7 9 13`

## Parser stuff (if we want / get time)

