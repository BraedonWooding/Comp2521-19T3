#Week 3 Binary Search Trees(BSTs)

The following website may help to visualise recursion [here](https://visualgo.net/en/recursion) I'll give updating the Big O tool to support functions and a way to visualise the callstack a go maybe this week or next.

For the tutorial we will consider the following tree :

```c typedef struct BSTNode *BSTree;
typedef struct BSTNode {
  int value;
  BSTree left;
  BSTree right;
} BSTNode;
```

    ![](assets / img / tree - orders.png)

        I think it is easier to visualise how to handle the orders via some
            code.The basic way to recurse through a BST is :

```c void recurse_bst(BSTree tree) {
  if (tree != NULL) {
    // 1)
    recurse_bst(tree->left);
    // 2)
    recurse_bst(tree->right);
    // 3)
  }
}
```

    Now we can place the following line `printf("%d ", tree->value);` at any one of the positions 1) 2) and 3).

What happens to the order when we do?

1. We print out our node before we do our 'children' this is called 'prefix'
2. We do it after our left node i.e. we are in the middle of our two children we call this 'infix'
3. We do it at the end this is called 'postfix'

?> Are there any trees that have infix == prefix?

> Yes if you only had right nodes than it would have infix == prefix effectively giving you a linked list

?> Are there any trees that will have all orders be the same

> Ones with a single node (or NULL!)

## Some terminology

- Every node (excluding the root) are connected by a directed edge (can be bidirectional in some setups) from exactly one other node this node is called a parent.  On the other hand you can be connected to multiple other nodes they are called your 'children'.
- Leafs have no children nodes
- Root nodes have no parents
- Depth of a node is the number of edges from the root to that node (0 for empty tree)
- Depth of a tree is the max number of nodes from the root to any leaf (0 for empty tree)
- Height of a node is the number of nodes from the node to the deepest leaf (0 for empty tree and 0 for leafs)
- Note Height of a tree == Depth of a tree. (0 for empty tree)

## Some Exercises

The answers to all coding exercises are under Tute3_Files right [here](https://github.com/BraedonWooding/Comp2521-19T3/tree/master/Tute3_Files)

### Count Internal

Implement the following; find and return the number of non leaf nodes in a binary tree.

```c
                                                                       int countInternal(BSTree t) {
  // If it is a leaf than we don't want to count it!
  // NOTE: leaf nodes have 0 children that is left == NULL
  //       AND right == NULL
  if (t == NULL || (t->left == NULL && t->right == NULL)) {
    return 0;
  }
  // Else consider the box model we talked about
  // We are choosing two smaller boxes of the left and right trees
  // And adding our node as an internal node since we
  // Know it MUST have children
  return 1 + countInternal(t->left) + countInternal(t->right);
}
```

### Node Depth

Finds the depth of the given node containing key.  If no node contains key return -1.  Perform in O(log n) IF tree is balanced.

```c
int nodeDepth(BSTree t, int key) {
  int depth;
  if (t == NULL) {
    // If we didn't find the node
    // We know it can't be in an empty tree
    return -1;
  } else if (key == t->value) {
    // If we found the node than we know that in this box
    // It has to have a depth of 1.  Remember we can't
    // think about the larger boxes that this is contained in
    // Just think about this by itself in it's own little tree
    return 1;
  } else if (key < t->value) {
    // (The logic for right is the same as this so I'll say it once)
    // Else we know that the key either doesn't exist or is in the
    // left tree so we'll query that.
    depth = nodeDepth(t->left, key);
  } else {
    depth = nodeDepth(t->right, key);
  }
  // If it turns out that we didn't find it
  // Then we don't want to include our node
  // If we did find it than we want to include our node
  // as part of the path.
  if (depth != -1) {
    depth++;
  }
  return depth;
}
```

### Max Branch Length

Find the height of a tree. i.e. the maximum branch length if a branch is a path from root to a leaf.

```c
int BSTreeMaxBranchLen(BSTree t) {
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
```

## Can we apply Postfix to other things?

Yes!

For example let's print out a linked list in reverse :O.  But you can't edit the list OR malloc or any crazy stuff!

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct LLNode *LList;
typedef struct LLNode {
  LList next;
  int value;
} LLNode;

void print_reverse(LList list);

int main(int argc, char *argv[]) {
  LList head = NULL;

  // Q: Why do it backwards?
  for (int i = argc - 1; i >= 1; i--) {
    LList new = malloc(sizeof *new);
    new->next = head;
    new->value = atoi(argv[i]);
    head = new;
  }
  print_reverse(head);
  putchar('\n');
  return 0;
}

void print_reverse(LList list) {
  if (list == NULL) {
    printf("X");
  } else {
    print_reverse(list->next);
    printf(" <- %d", list->value);
  }
}
```
