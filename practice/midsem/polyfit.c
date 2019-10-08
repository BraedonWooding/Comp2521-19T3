#include "list.h"

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

    NOTE: How efficient can you make this?
*/
int polyfit(List list, double *coefficients, int coefficients_len) {
    // TODO:
    return 0;
}
