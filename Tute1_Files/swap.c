void swap(int *array, int i, int j) {
  int tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

#include <string.h>

// @NOTE!  This part is way past the scope of the course
// It was just because I mentioned it in the tute
// You don't need to know why / how this works but I felt
// it may be interesting

// this swap is more generic but ruins type safety
// you should aim for other solutions this is typically
// the wrong way
void swap_ptr(void *a, void *b, int size) {
  unsigned char temp;
  // unsigned just means only positive
  unsigned char *bytes_a = (unsigned char*)a;
  unsigned char *bytes_b = (unsigned char*)b;

  // this just swaps each byte one by one
  for (int i = 0; i < size; i++) {
    temp = bytes_a[i];
    bytes_a[i] = bytes_b[i];
    bytes_b[i] = temp;
  }
}

// you would call it like
// swap_ptr(array[i], array[j], sizeof(int))
// you can also write a wrapper for the array if you want
void swap_array_index(void *array, int i, int j, int size) {
  unsigned char *bytes_array = (unsigned char*)array;
  swap_ptr(&bytes_array[i * size], &bytes_array[j * size], size);
}
