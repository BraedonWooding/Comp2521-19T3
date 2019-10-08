#include "list.h"
#include <stdlib.h>

extern int polyfit(List list, double *coefficients, int coefficient_len);

int main(void) {
    List list = readList();

    // the next number in stdin is the result
    int res;
    scanf("%d", &res);
    // then the next n numbers are the coefficients
    int len;
    scanf("%d", &len);
    double *coeff = malloc(sizeof(*coeff) * len);
    for (int i = 0; i < len; i++) {
        scanf("%lf", &coeff[i]);
    }

    // !! to convert it to just a 1 or 0
    // i.e. !!5 = !0 = 1.
    //      !!0 = !1 = 0.
    //      !!1 = !0 = 1
    if (!!polyfit(list, coeff, len) != !!res) {
        printList(list);
        printf(res ? "Should fit the curve: " : "Shouldn't fit the curve: ");
        for (int i = 0; i < len; i++) printf("%lf ", coeff[i]);
        putchar('\n');
        abort();
    }
    freeList(list);
}