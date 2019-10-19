#include "list.h"

int listDeleteLargest(List l) {
  // NOTE: list can't be empty
  int max = l->head->value;
  Node delete = l->head;
  Node prev = NULL;
  Node cur = l->head;
  while (cur->next != NULL) {
    if (cur->next->value > max) {
      delete = cur->next;
      prev = cur;
      max = cur->next->value;
    }
    cur = cur->next;
  }

  if (prev != NULL) {
    prev->next = delete->next;
  } else {
    l->head = delete->next;
  }
  free(delete);
  return max;
}
