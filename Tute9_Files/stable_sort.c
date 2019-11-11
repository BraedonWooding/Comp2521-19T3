#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id;
  int value;
} Item;

Item *parse_array(char *str, int *out_len) {
  char *end;
  Item *list = malloc(sizeof(*list) * 4);
  *out_len = 0;
  int cur_len = 4;

  while (*str) {
    int v = (int)strtol(str, &end, 10);
    // end should point to the extra character
    if (*end >= 'a' && *end <= 'z') {
      if (*out_len == cur_len) {
        list = realloc(list, (cur_len *= 2) * sizeof(*list));
      }
      list[(*out_len)++] = (Item){.value = v, .id = *(end++)};
    } else {
      fprintf(stderr, "Missing an extra character (lowercase alphabetical)\n");
      exit(1);
    }
    str = end;
  }
  // shrink back down
  list = realloc(list, *out_len * sizeof(*list));

  return list;
}

int binary_search_item(Item to_find, Item list[], int len) {
  int lo = 0;
  int hi = len - 1;
  int index = -1;

  while (lo <= hi) {
    // to prevent integer overflow
    int mid = lo + (hi - lo) / 2;
    if (list[mid].value == to_find.value) {
      // linearly search from this point
      // could be to left or right
      // NOTE: we could also check to make sure value holds
      //       but you'll find that it is practically the same behaviour
      for (int offset = 0;
           index == -1 && (mid + offset < len || mid - offset >= 0); offset++) {
        if (mid + offset < len && list[mid + offset].id == to_find.id) {
          index = mid + offset;
        } else if (mid - offset >= 0 && list[mid - offset].id == to_find.id) {
          index = mid - offset;
        }
      }
      // if we don't find anything in the search it'll break at the bounds
      break;
    } else if (list[mid].value > to_find.value) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  return index;
}

/*
 * You only really wanted a lo / hi when you are dealing with recursion
 * It's almost always easier to use to just have a length and use pointer
 * arithmetic If you want to move the lower part
 */
int is_stable_sort(Item original[], Item sorted[], int len) {
  // a poor man's hashtable we are storing them based on index
  int *has_seen = malloc(sizeof(*has_seen) * len);
  memset(has_seen, 0, sizeof(*has_seen) * len);

  // O(n log n) complexity
  for (int i = 0; i < len; i++) {
    // For each key in original find sorted one using binary search
    // NOTE: This does degrade to O(n^2) if all keys have same value
    //       but different ids but that is a relatively easy fix
    //       using some preprocessing (just didn't feel it was important)
    int index = binary_search_item(original[i], sorted, len);
    if (index == -1) {
      fprintf(
          stderr,
          "List's must contain the same elements sorted doesn't have %d%c\n",
          original[i].value, original[i].id);
      exit(1);
    }

    has_seen[index] = 1;

    // if we have seen the one after us and the value is higher
    // then it means our stable sort validation is wrong!
    // non-stable
    if (index < len - 1 && has_seen[index + 1] &&
        sorted[index + 1].value == sorted[index].value) {
      return 0;
    }
  }

  free(has_seen);
  return 1;
}

// Supply 2 arrays that are quoted
// First is original second is sorted
int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr,
            "Usage ./stable_sort \"<Original Array>\" \"<Sorted Array>\"\n");
    fprintf(stderr,
            "i.e. ./stable_sort \"2a 2b 1a 9a 3a\" \"1a 2a 2b 3a 9a\"\n");
    exit(1);
  }

  int original_len;
  Item *original = parse_array(argv[1], &original_len);

  int sorted_len;
  Item *sorted = parse_array(argv[2], &sorted_len);

  if (original_len != sorted_len) {
    fprintf(stderr,
            "Original length (%d) should be the same as Sorted length (%d)\n",
            original_len, sorted_len);
    exit(1);
  }

  puts(is_stable_sort(original, sorted, original_len) ? "Is stable\n"
                                                      : "Is non stable\n");
  return 0;
}
