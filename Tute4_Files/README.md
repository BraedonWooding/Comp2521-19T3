# Week 4 (BST + Revision)

## Height Difference (I don't really like this Question eh)

For each node in the tree print out the difference between the 2 subtrees.

And return the height of the tree.  To not make this question feel nice if it is an empty tree do nothing.

```c
int printHeightDiff(BSTree t) {
  // TODO:
}
```

## Can we detect if a tree is balanced?

?> What makes a balanced tree

NOTE: This question is a bit different from the tute because I just trimmed the fat from the question.

```c
int isHeightBalanced(BSTree t) {
  // TODO:
}
```

## Computing the width of a tree

- If the tree is empty it has width 0
- A tree with a single node has width of 3
- All other trees have width which is 3 more than the sum of the width of their children

```c
int BSTWidth(BSTree t) {
  // TODO:
}
```

![Tree Widths](assets/img/tree-widths.png)

## GDB + Valgrind :O

[here](gdb_valgrind)

## Some more example Midsem questions

I probably won't do any of these during the tute just no time.  But we'll see :).

For all these questions you have the following structures

```c
typedef struct node_t {
    struct node_t *next;
    int value;
} Node;

typedef struct bst_t {
    struct bst_t *left;
    struct bst_t *right;
    int value;
} BST;
```

The midsem practice paper indicates that you need to be good at both linked lists and binary trees.

Please do both the practice paper and the practice exercises from [here](https://webcms3.cse.unsw.edu.au/COMP2521/19T3/resources/34197).

But here is a good overview of all of them :).

!> Currently I don't have any test files for these but I'm working on them I'll get them done by Thursday (sorry!).

### Searching in Linked Lists

#### Reverse List (Version 2!)

This time we want to reverse the list but we are to edit the list.  We can't malloc however so purely just edit the list.

`Node *reverse(Node *list);`

?> Can we do this recursively nicely?

#### List Difference

Given 2 lists return a new list which is the difference of the two sets.

Difference is defined as being a list of all the nodes that aren't common. i.e. given `[1, 2, 3]` and `[2, 3, 9]` the difference is `[1, 9]`.

`Node *difference(Node *a, Node *b);`

#### Polynomial Curve (harder question for fun)

Given an array of coefficients and a length determine if the linked list fits.  Return 1 if it fits else return 0.

`int polyfit(Node *node, double coefficients[], int len);`

> Note round the double result to the closest int. i.e. 3.5 => 4, -0.8 => -1.

For example given the list `[1, 2, 3, 4, 5]` it fits to the coefficient array `[1, 1]` which is the function `1 + x`.

Some more examples:

- `[0, 1, 4, 9, 16, 25]` fits to the coefficient array `[0, 0, 1]` which is the function `0 + 0x + x^2`.
- `[0, 1, 1, 0, -1, -1, 0, 1, 1, 0]` fits to the coefficient array `[0, 1, 0, -1/6, 0, 1/120, -1/5040]` is the function `x - x^3/3! + x^5/5! - x^7/7!` which is actually approximately `sin (x)` using what we call a Taylor Expansion

### Searching BST

#### Postfix, Prefix, Infix Order

Print out the tree in all 3 orders.

#### Insert BST in a flipped order

i.e. instead of having smaller nodes on the left have smaller nodes on the right.

#### Sum all powers of 2 inside BSTNode

Given a BST tree sum all the nodes that are powers of 2 i.e. 2, 4, 8, 16, 32, 64, ...

