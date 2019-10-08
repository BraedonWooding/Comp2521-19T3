/*
 * =====================================================================================
 *
 *       Filename:  bad.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/19 09:22:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Braedon Wooding (bw), braedon.wooding@student.unsw.edu.au
 *   Organization:  UNSW
 *
 * =====================================================================================
 */

#include <stdlib.h>

struct a {
  int a;
  int b;
};

int main(void) {
  struct a *A = NULL;
  printf("%d\n", A->b);
  return 0;
}

