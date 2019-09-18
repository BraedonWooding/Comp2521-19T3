#include <stdlib.h>

typedef struct _node_t {
  int value;
  struct _node_t *next;
} Node;

/*
  Think of smaller boxes inside larger ones

  i.e. for the list 1 -> 2 -> 3 -> X
  We would have the boxes

  |---| +1
  | 1 |---| +2
  | 2 | 2 |---| +3
  | 3 | 3 | 3 |---| +4
  | 4 | 4 | 4 | 4 |---| +0
  | X | X | X | X | X |
  |-------------------|
 */
int sum_rec(Node *list) {
  if (list == NULL) {
    return 0;
  }
  return list->value + sum_rec(list->next);
}

/*
  Identical to the while function but using for
 */
int sum_for(Node *list) {
  int sum = 0;
  for (Node *cur = list; cur != NULL; cur = cur->next) {
    sum += cur->value;
  }
  return sum;
}

int sum_while(Node *list) {
  int sum = 0;
  Node *cur = list;
  while (cur != NULL) {
    sum += cur->value;
    cur = cur->next;
  }
  return sum;
}
