
#include "list.h"

bool listIsPalindromic(List l) {
  Node front = l->first;
  Node back = l->last;
  while (front != back && back->next != front) {
    if (front->value != back->value)
      return false;
    front = front->next;
    back = back->prev;
  }

  return true;
}
