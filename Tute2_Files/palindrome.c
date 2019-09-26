/*
  palindrome S do
    i = 0, j = strlen(S) - 1
    while i < j do
      if S[i] != S[j] then
         return false
      endif
      i++, j--
    end
    return true
  end
 */

// O(n)

#include <string.h>

int palindrome(const char *str) {
  int i = 0, j = strlen(str) - 1;
  while (i < j) {
    if (str[i] != str[j]) {
      return 0;
    }
    i++, j--;
  }
  return 1;
}
