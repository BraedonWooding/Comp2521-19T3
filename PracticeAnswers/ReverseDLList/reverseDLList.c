
#include "list.h"

void reverseDLList(List l) {
  Node cur = l->first;
  l->first = l->last;
  l->last = cur;

  while (cur != NULL) {
    // A little weird so you may want to draw a picture
    // I'll bring paper to the exam for people to use
    Node tmp = cur->prev;
    cur->prev = cur->next;
    cur->next = tmp;
    cur = cur->prev;
  }
}

