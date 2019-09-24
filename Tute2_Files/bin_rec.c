#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Note a lot of stuff online does this differently
  I prefer this method since it's a little nicer to think how it works
  But the edge cases are hard to visualise!!!
 */
int bin_search(int array[], int wanted, int len) {
  if (len <= 0) {
    return -1;
  }

  // My confusion was primarily to do with this
  // In normal BinarySearch you do (lo + hi) / 2
  // (Well actually you do lo + (hi - lo) / 2 so you don't overflow)
  // I took the incorrect presumption that this would
  // carry over to this case (which it sometimes can)
  // But not with how I was tackling the problem
  // In this case you just take len / 2 i.e. the middle
  int m = len / 2;

  // First two cases remain the same :) atleast i got those right!
  if (array[m] == wanted) {
    return m;
  } else if (array[m] > wanted) {
    return bin_search(array, wanted, m);
  } else {
    // This case remains basically the same
    // As said before the length will always be length / 2
    // (you are chucking out half the array)
    int pos = bin_search(&array[m + 1], wanted, m);
    if (pos != -1) {
      // Since we moved the array forward
      // We have to correct the position :)
      // Since the position will be presuming
      // the array starts at m + 1
      pos += m + 1;
    }
    return pos;
  }
}

// A collection of tests for you to verify that it is indeed correct
// :)
int main(void) {
  int a1[13] = {-30, -20, -10, 1, 2, 5, 9, 10, 15, 100, 1000, 2000, 500000};
  for (int i = 0; i < 13; i++) {
    assert(bin_search(a1, a1[i], 13) == i);
  }
  for (int rand = -100; rand < -50; rand++) {
    assert(bin_search(a1, rand, 13) == -1);
  }
  for (int rand = 101; rand < 400; rand++) {
    assert(bin_search(a1, rand, 13) == -1);
  }
  assert(bin_search(a1, 0, 13) == -1);
  assert(bin_search(a1, INT32_MAX, 13) == -1);
  assert(bin_search(a1, INT32_MIN, 13) == -1);
}
