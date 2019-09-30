# Week 3 Binary Search Trees (BSTs)

For the tutorial we will consider the following tree:

```c
typedef struct BSTNode *BSTree;
typedef struct BSTNode {
	int value;
	BSTree left;
	BSTree right;
} BSTNode;
```

![](assets/img/tree-orders.png)

I think it is easier to visualise how to handle the orders via some code.  The basic way to recurse through a BST is:

```c
void recurse_bst(BSTree tree) {
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

?> Are there any trees that will have all orders be the same

## Extension design some code to print out levels

Print it out in level order.

Introduction to BFS vs DFS

## Some terminology

- Every node (excluding the root) are connected by a directed edge (can be bidirectional in some setups) from exactly one other node this node is called a parent.  On the other hand you can be connected to multiple other nodes they are called your 'children'.
- Leafs have no children nodes
- Root nodes have no parents
- Depth of a node is the number of edges from the root to that node (0 for empty tree)
- Depth of a tree is the max number of nodes from the root to any leaf (0 for empty tree)
- Height of a node is the number of nodes from the node to the deepest leaf (0 for empty tree and 0 for leafs)
- Note Height of a tree == Depth of a tree. (0 for empty tree)

## Some Exercises

### Count Internal

Implement the following; find and return the number of non leaf nodes in a binary tree.

```c
int countInternal(BSTree t) {
  return 42;
}
```

### Node Depth

Finds the depth of the given node containing key.  If no node contains key return -1.  Perform in O(log n) IF tree is balanced.

```c
int nodeDepth(BSTree t, int key) {
  return -1;
}
```

### Max Branch Length

Find the height of a tree. i.e. the maximum branch length if a branch is a path from root to a leaf.

```c
int BSTreeMaxBranchLen(BSTree t) {
  return 42;
}
```

## Can we apply Postfix to other things?

Yes!

For example let's print out a linked list in reverse :O.  But you can't edit the list OR malloc or any crazy stuff!

```c
#include <stdlib.h>
#include <stdio.h>

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
  return 0;
}

// How would you normally do it without creating a new list?
void print_reverse(LList list) {
  // TODO:
}
```

