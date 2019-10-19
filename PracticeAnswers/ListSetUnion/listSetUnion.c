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

void listAdd(List list, List result) {
  Node cur = list->head;
  while (cur != NULL) {
    if (!listContains(result, cur->value)) {
      Node n = newNode(cur->value);
      n->next = result->head;
      result->head = n;
    }
    cur = cur->next;
  }
}

List listSetUnion(List s1, List s2) {
  List result = newList();
  listAdd(s1, result);
  listAdd(s2, result);
  return result;
}
