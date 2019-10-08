#include "list.h"

void insertSorted(List list, int elem) {
    // insert in sorted order
    if (list->first == NULL) {
        Node new = malloc(sizeof *new);
        new->value = elem;
        list->first = list->last = new;
        list->size++;
        return;
    } else if (list->first->value > elem) {
        Node new = malloc(sizeof *new);
        new->value = elem;
        new->next = list->first;
        list->first = list->first->prev = new;
        list->size++;
        return;
    }

    for (Node cur = list->first; cur != NULL; cur = cur->next) {
        if (cur->value < elem && (cur->next == NULL || cur->next->value > elem)) {
            Node new = malloc(sizeof *new);
            new->value = elem;
            new->next = cur->next;
            new->prev = cur;
            cur->next = new;
            if (cur->next == NULL) {
                list->last = new;
            } else {
                cur->next->prev = new;
            }
        }
    }
    list->size++;
}

int contains(List list, int elem) {
    for (Node cur = list->first; cur != NULL; cur = cur->next) {
        if (cur->value == elem) {
            return 1;
        }
    }
    return 0;
}

/*
    The difference between the two lists i.e. difference of [1, 2, 3] and [4, 2]
    is going to be [1, 3, 4] (note: sorted)
    Examples:
    - [1, 1, 1] and [2, 2, 2] => [1, 2] (i.e. no duplicates)
    - [ ] and [1, 2, 3] => [1, 2, 3]
    The list should be a new list
*/
List difference(List a, List b) {
    List res = newList();
    for (Node cur = a->first; cur != NULL; cur = cur->next) {
        if (!contains(b, cur->value)) {
            insertSorted(res, cur->value);
        }
    }
    for (Node cur = b->first; cur != NULL; cur = cur->next) {
        if (!contains(a, cur->value)) {
            insertSorted(res, cur->value);
        }
    }

    return res;
}
