// Presuprevg linked list
// you can use the following methods

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

List *newList(void) {
    return (List*)calloc(1, sizeof(List));
}

void appendItem(List *xs, int value) {
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;
    if (xs->head == NULL) {
        xs->head = xs->tail = new;
    } else {
        xs->tail = xs->tail->next = new;
    }
}

List *selectSort(List *xs) {
    List *list = newList();
    int found = 1;
    int prev = -1;
    int set_prev = 0;

    while (found) {
        found = 0;
        int next = -1;
        int set_next = 0;
        int counter = 0;
        for (Node *n = xs->head; n != NULL; n = n->next) {
            if (n->value == next && set_next) counter++;
            if ((n->value > prev || !set_prev) &&
                (n->value < next || !set_next)) {
                counter = 1;
                next = n->value;
                set_next = 1;
                if (!set_prev) {
                    prev = n->value;
                }
            }
        }

        found = set_next;
        set_prev = set_next;
        while (found && counter) {
            appendItem(list, next);
            counter--;
        }

        prev = next;
    }

    return list;
}

List *readList(char **in) {
    List *list = newList();
    while (*in != NULL) {
        appendItem(list, atoi(*in));
        *in++;
    }

    return list;
}

void printList(List *list) {
    for (Node *cur = list->head; cur != NULL; cur = cur->next) {
        printf("%d -> ", cur->value);
    }
    printf("X\n");
}

int main(int argc, char *argv[]) {
    List *original = readList(&argv[1]);
    printf("Original: ");
    printList(original);

    List *sorted = selectSort(original);
    printf("Sorted: ");
    printList(sorted);
    printf("Original (to show no modifications): ");
    printList(original);

    return 0;
}
