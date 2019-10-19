// getPeaks.c
// Written by Ashesh Mahidadia, August 2017

#include "DLList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for
    detailed specification and description of your task.

    - DO NOT modify code in the file DLList.h .
    - You can add helper functions in this file.
    - DO NOT add "main" function in this file.
*/

DLList getPeaks(DLList L) {
  DLList peaksL = newDLList();
  DLListNode *cur = L->first;
  while (cur != NULL) {
    if (cur->prev && cur->prev->value < cur->value && cur->next &&
        cur->value > cur->next->value) {
      DLListNode *new = newDLListNode(cur->value);
      if (peaksL->first == NULL) {
        peaksL->first = new;
        peaksL->last = new;
        peaksL->curr = new;
      } else {
        new->prev = peaksL->last;
        peaksL->last->next = new;
        peaksL->last = new;
      }
      peaksL->nitems++;
    }
    cur = cur->next;
  }

  return peaksL;
}
