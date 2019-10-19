
#include "list.h"

void listReverse(List l) {
  // You can do this recursively
  Node head = NULL;
  Node cur = l->head;
  while (cur != NULL) {
    Node next = cur->next;
    cur->next = head;
    head = cur;
    cur = next;
  }
  l->head = head;
}
