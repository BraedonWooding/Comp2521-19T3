# Week 4 (BST + Revision)

## Height Difference

For each node in the tree print out the difference between the 2 subtrees.

And return the height of the tree.  To not make this question feel nice if it is an empty tree do nothing.

```c
int printHeightDiff(BSTree t) {
  if (t == NULL) {
        return 0;
    } else {
        int left = printHeightDiff(t->left);
        int right = printHeightDiff(t->right);
        int diff;
        int height;
        if (left > right) {
            diff = left - right;
            height = left + 1;
        } else {
            diff = right - left;
            height = right + 1;
        }
        printf("%d diff: %d\n", t->value, diff);
        return height;
    }
}
```

## Can we detect if a tree is balanced?

?> What makes a balanced tree

```c
#include TREE_IS_NOT_BALANCED (-99)

int isHeightBalanced(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = isBalanced(t->left);
        int right = isBalanced(t->right);
        int diff;
        int height;
        if (left > right) {
            diff = left - right;
            height = left + 1;
        } else {
            diff = right - left;
            height = right + 1;
        }
        if (diff > 1) {
            return TREE_IS_NOT_BALANCED;
        }
        return height;
    }
}
```

## Computing the width of a tree

- If the tree is empty it has width 0
- A tree with a single node has width of 3
- All other trees have width which is 3 more than the sum of the width of their children

?> Kind of a useless question since its not really always correct but eh still along the same idea as the rest.

```c
int numNodes(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = numNodes(t->left);
        int right = numNodes(t->right);
        return left + right + 1;
    }
}

int widthNumNodes(BSTree t) {
    return numNodes(t) * 3;
}

int width(BSTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = width(t->left);
        int right = width(t->right);
        return left + right + 3;
    }
}
}
```

![Tree Widths](assets/img/tree-widths.png)

## GDB + Valgrind :O

[here](gdb_valgrind)

## Some more example Midsem questions

I probably won't do any of these during the tute just no time.  But we'll see :).

The midsem practice paper indicates that you need to be good at both linked lists and binary trees.

Please do both the practice paper and the practice exercises from [here](https://webcms3.cse.unsw.edu.au/COMP2521/19T3/resources/34197).

There are more questions [here](midsem_questions)
