
#include "list.h"

bool listIsOrdered(List l) {
  if (l->head == NULL || l->head->next == NULL)
    return true;

  Node cur = l->head;
  bool descending = cur->value > cur->next->value;

  while (cur->next != NULL) {
    // You could spend time making this more concise
    // But sometimes just a dirty quick way of doing something
    // Is best in exams.
    if ((descending && cur->value < cur->next->value) ||
        (!descending && cur->value > cur->next->value)) {
      return false;
    }
    cur = cur->next;
  }
  return true;
}
