/*
 == TUESDAY TUTE INFORMATION ==
  My confusion was primarily to do with this
  In normal BinarySearch you do (lo + hi) / 2
  (Well actually you do lo + (hi - lo) / 2 so you don't overflow)
  I took the incorrect presumption that this would
  carry over to this case (which it sometimes can)
  But not with how I was tackling the problem
  In this case you just take len / 2 i.e. the middle
 */

// Includes are for the tests
#include <assert.h>
#include <inttypes.h>

/*
 Visualise it as smaller and smaller boxes
 i.e. for the array [ 1 2 3 4 10 ]

 It is really just visualised as:
 [ [ [1] [2] ] 3 [ [4] [10] ]  ]
 */
int bin_search(int array[], int len, int wanted) {
  // Base case 1)  We can't find what we want in an empty array
  if (len <= 0) {
    return -1;
  }

  /*
   You can also make this (len - 1) / 2 if you
   prefer the similarity to the standard binary search

   In consequence when passing in the length to
   the recursive calls it would be len / 2 rather than m
   */
  int m = len / 2;
  if (array[m] == wanted) {
    // Base case 2) We found what we want
    return m;
  } else if (array[m] < wanted) {
    // Recursive case 1) We want to go right
    // So the array now begins at m + 1 and goes for len / 2
    int pos = bin_search(&array[m + 1], m, wanted);
    if (pos != -1) {
      pos += m + 1;
    }
    return pos;
  } else {
    // Recursive case 2) We want to go left
    // So the array length gets shortened
    // But it still starts at 0
    return bin_search(array, m, wanted);
  }
}

// A collection of tests for you to verify that it is indeed correct
// :)
int main(void) {
  int a1[13] = {-30, -20, -10, 1, 2, 5, 9, 10, 15, 100, 1000, 2000, 500000};
  for (int i = 0; i < 13; i++) {
    assert(bin_search(a1, 13, a1[i]) == i);
  }
  for (int rand = -100; rand < -50; rand++) {
    assert(bin_search(a1, 13, rand) == -1);
  }
  for (int rand = 101; rand < 400; rand++) {
    assert(bin_search(a1, 13, rand) == -1);
  }
  assert(bin_search(a1, 0, 13) == -1);
  assert(bin_search(a1, 13, INT32_MAX) == -1);
  assert(bin_search(a1, 13, INT32_MIN) == -1);
}
