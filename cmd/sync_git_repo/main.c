#include <stdio.h>
#include <unistd.h>

#include "c/color_print.h"
#include "c/git.h"
#include "c/path.h"

#define MAX_PATH_LEN 100

error_t handle_repo(char* path) {
  char normalized_path[MAX_PATH_LEN];
  if (OK != expand_tilde_path(path, normalized_path)) {
    color_printf(COLOR_ERROR, "Error: not a valid path\n  Repo at: %s\n", path);
    return -1;
  }

  if (OK != access(normalized_path, F_OK)) {
    color_printf(COLOR_FYI, "Skip repository as not existed\n  Repo at: %s\n",
                 normalized_path);
    return OK;
  }

  color_printf(COLOR_INFO, "Pulling: %s\n", normalized_path);

  git_status_t git_status;
  /* Life time of git_status is same as normalized_path. */
  git_status.path = normalized_path;

  /* For any `git_read` failure, we just log them. return value is zero. */
  if (OK == git_read(&git_status)) {
    color_print(COLOR_SUCCESS, "Success.\n");
  } else {
    color_printf(COLOR_ERROR, "Error: failed to pull the git repo.\n  Repo at: %s\n",
                 normalized_path);
  }

  return OK;
}

int main() {
  char* repos[] = {
      "~/Workspace/dotfiles",    "~/Workspace/vimrc", "~/Workspace/mlvm",
      "~/Workspace/dockerfiles", "~/Workspace/notes",
  };

  int repo_count = sizeof(repos) / sizeof(char*);
  int i;

  for (i = 0; i < repo_count; ++i) {
    if (OK != handle_repo(repos[i])) return -1;
  }

  return 0;
}
