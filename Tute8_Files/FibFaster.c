#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int fibR(int n, int *memoized) {
    if (memoized[n] == 0) {
        memoized[n] = fibR(n - 1, memoized) + memoized[n - 2];
    }
    return memoized[n];
}

int fib(int n) {
    assert(n >= 0);
    // calloc just zero fills the memory i.e. memset
    // n + 1 to allow us to index [n]
    int *memoized = calloc(n + 1, sizeof(int));
    assert(memoized != NULL);
    memoized[0] = 1;
    memoized[1] = 1;
    int f = fibR(n, memoized);
    free(memoized);
    return f;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
      fprintf(stderr, "Usage ./fib <NUM>\n");
      exit(1);
    }
    printf("%d\n", fib(atoi(argv[1])));
    return 0;
}
