#include <stdio.h>

#include "c/path.h"

int main() {
  char path[100];
  if (expand_tilde_path("~/.vimrc", path) != 0)
    return -1;

  printf("Hello %s\n", path);
  return 0;
}
