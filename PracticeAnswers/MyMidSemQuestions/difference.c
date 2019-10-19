#include "list.h"

void addSorted(List l, Node item) {
  l->size++;
  if (l->first == NULL) {
    l->first = l->last = item;
  } else if (l->last->value < item->value) {
    l->last->next = item;
    item->prev = l->last;
    l->last = item;
  } else {
    Node cur = l->first;
    while (cur->value < item->value) {
      cur = cur->next;
    }

    cur->prev->next = item;
    item->prev = cur->prev;
    cur->prev = item;
    item->next = cur;
  }
}

bool listContains(List a, int value) {
  Node cur = a->first;
  while (cur != NULL) {
    if (cur->value == value) {
      return true;
    }
    cur = cur->next;
  }
  return false;
}

void addList(List a, List b, List result) {
  Node cur = a->first;
  while (cur != NULL) {
    if (listContains(b, cur->value) == false &&
        listContains(result, cur->value) == false) {
      Node new = malloc(sizeof(*new));
      new->next = new->prev = NULL;
      new->value = cur->value;
      addSorted(result, new);
    }
    cur = cur->next;
  }
}

/*
    The difference between the two lists i.e. difference of [1, 2, 3] and [4,
   2] is going to be [1, 3, 4] (note: sorted) Examples:
    - [1, 1, 1] and [2, 2, 2] => [1, 2] (i.e. no duplicates)
    - [ ] and [1, 2, 3] => [1, 2, 3]
    The list should be a new list
*/
List difference(List a, List b) {
  // NOTE: We can presume the list is sorted but I'll write it as if you
  // couldn't just for those that didn't realise it.
  List result = newList();
  addList(a, b, result);
  addList(b, a, result);
  return result;
}
