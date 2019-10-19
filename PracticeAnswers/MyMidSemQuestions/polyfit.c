#include "list.h"

// This is just an O(m) function (m being the length of coefficients)
// We can actually make this much much much more efficient by using taylor series expansions
// To approximate the polynomial however this carries a lot of complexity
// Since we would have to make sure we don't have large errors from the approximation
// And suitably fix those
int eval(double *coefficients, int coefficients_len, int x) {
  double result = 0;
  int x_eval = 1;
  int i = 0;
  while (i < coefficients_len) {
    result += coefficients[i] * x_eval;
    x_eval *= x;
    i++;
  }
  // + 0.5 to round
  return result + 0.5;
}

/*
    Does the list fit the given coefficient curve.

    For example if we have list 1 -> 2 -> 3
    It can be represented via a line with points (0, 1), (1, 2), (2, 3)
      /
     /
    /
    And will fit the curve 1 + 1 * x which is the coefficient array [1, 1]

    Some more examples:
    The list 0 -> 1 -> 4 -> 9 -> 16 -> 25 is a list of points of
    (0, 0), (1, 1), (2, 4), (3, 9), (4, 16), (5, 25) and will fit the curve x^2
    which is the coefficient array [0, 0, 1].

    NOTE: How efficient can you make this? With m being coefficients_len and n being list length
    > Technically you can make it upwards of linear (i.e. O(n + m)) but most people will make a O(n m) solution
    > You can make it linear by using forward differencing and taylor series expansion to approximate the poly
*/
int polyfit(List list, double *coefficients, int coefficients_len) {
  Node cur = list->first;
  int i = 0;
  while (cur != NULL) {
    if (eval(coefficients, coefficients_len, i) != cur->value) {
      return false;
    }
    cur = cur->next;
    i++;
  }
  return true;
}
