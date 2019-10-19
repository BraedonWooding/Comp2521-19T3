
#include "list.h"

int numDupesInOrderedList(List l) {
  int numDupes = 0;
  Node cur = l->head;
  Node dupe = NULL;
  while (cur != NULL) {
    if (dupe && dupe->value == cur->value) {
      numDupes++;
    } else {
      dupe = cur;
    }
    cur = cur->next;
  }
  return numDupes;
}
