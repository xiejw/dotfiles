#include <stdio.h>

#include "c/git.h"
#include "c/path.h"

#define MAX_PATH_LEN 100

int handle_repo(char* path) {
  DECLARE_ERROR(err);

  char normalized_path[MAX_PATH_LEN];
  if (0 != expand_tilde_path(path, normalized_path)) {
    FREE_ERROR(err);
    return -1;
  }

  printf("\033[1;36mPulling: %s\033[0m\n", normalized_path);

  git_status_t git_status;
  /* Lifttime of git_status is same as normalized_path. */
  git_status.path = normalized_path;

  if (SUCCEEDED(err = git_read(&git_status))) {
    printf("\033[1;32mSuccess.\033[0m\n");
  } else {
    printf("\033[1;31mError: %s\n  Repo at: %s\033[0m\n", err->err_msg,
           normalized_path);
  }

  FREE_ERROR(err);
  return 0;
}

int main() {
  char* repos[] = {
      "~/Workspace/dotfiles",
      "~/Workspace/vimrc",
      "~/Workspace/mlvm",
  };

  int repo_count = sizeof(repos) / sizeof(char*);
  int i;

  for (i = 0; i < repo_count; ++i) {
    if (handle_repo(repos[i]) != 0) return -1;
  }

  return 0;
}
