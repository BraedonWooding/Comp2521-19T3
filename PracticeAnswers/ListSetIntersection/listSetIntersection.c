
#include "list.h"

bool listContains(List list, int value) {
  Node cur = list->head;
  while (cur != NULL) {
    if (cur->value == value) {
      return true;
    }
    cur = cur->next;
  }
  return false;
}

List listSetIntersection(List s1, List s2) {
  List result = newList();

  Node cur = s1->head;
  while (cur != NULL) {
    if (listContains(s2, cur->value)) {
      // Order doesn't matter but if it did
      // It isn't too much more work
      // Just another loop

      // NOTE: I recommend you remember this
      //       It is effectively a stack very
      //       Easy way to add to a list
      // No branches required to add!
      Node n = newNode(cur->value);
      n->next = result->head;
      result->head = n;
    }
    cur = cur->next;
  }

  return result;
}
