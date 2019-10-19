#include "list.h"
#include <stdlib.h>

extern List difference(List a, List b);

int matches(List a, List b) {
    Node cur_a, cur_b;
    for (cur_a = a->first, cur_b = b->first;
         cur_a != NULL && cur_b != NULL;
         cur_a = cur_a->next, cur_b = cur_b->next) {
        if (cur_a->value != cur_b->value) {
            return 0;
        }
    }
    return cur_a == NULL && cur_b == NULL;
}

int main(void) {
    List a = readList();
    List b = readList();
    List res = readList();
    List out = difference(a, b);
    if (!matches(out, res)) {
        printf("The lists don't match.  Your list is\n");
        printList(out);
        printf("The expected list is\n");
        printList(res);
        abort();
    }
    freeList(a);
    freeList(b);
    freeList(res);
}