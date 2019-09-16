#include "cpath.h"

int main(void) {
  cpath path = cpathFromUtf8("tmp");
  cpathMkdir(&path);

  for (cpath_char_t i = 1; i < 10; i++) {
    cpathAppendSprintf(&path, "/a%d", i);
    cpathMkdir(&path);

    for (cpath_char_t j = 1; j < 100; j++) {
      cpathAppendSprintf(&path, "/b%d", j);
      cpathMkdir(&path);

      for (cpath_char_t k = 1; k < 50; k++) {
        cpathAppendSprintf(&path, "/%d.tmp", k);
        FILE *f = cpathOpen(&path, CPATH_STR("w"));
        fclose(f);
        cpathUpDir(&path);
      }
      cpathUpDir(&path);
    }
    cpathUpDir(&path);
  }
  return 0;
}
