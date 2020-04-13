#include <stdio.h>

#include "c/path.h"

#define MAX_PATH_LEN 100

int handle_repo(char* path) {
  char normalized_path[MAX_PATH_LEN];
  if (expand_tilde_path(path, normalized_path) != 0) return -1;
  printf("-> Handling: %s\n", normalized_path);
  return 0;
}

int main() {
  char* repos[] = {
    "~/Workspace/dotfiles",
    "~/Workspace/vimrc",
    "~/Workspace/mlvm",
  };

  int repo_count = sizeof(repos)/sizeof(char*);
  int i;

  for (i = 0; i < repo_count; ++i) {
    if (handle_repo(repos[i]) != 0) return -1;
  }

  return 0;
}
