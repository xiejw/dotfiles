#include <stdio.h>
#include <unistd.h>

#include "c/git.h"
#include "c/path.h"
#include "c/color_print.h"

#define NO_SEVERE_ERROR 0
#define MAX_PATH_LEN 100

int handle_repo(char* path) {
  DECLARE_ERROR(err);

  char normalized_path[MAX_PATH_LEN];
  if (!SUCCEEDED(err = expand_tilde_path(path, normalized_path))) {
    color_printf(COLOR_ERROR, "Error: %s\n  Repo at: %s\n", err->err_msg, path);
    FREE_ERROR(err);
    return -1;
  }

  if (0 != access(normalized_path, F_OK)) {
    color_printf(COLOR_FYI, "Skip repository as not existed\n  Repo at: %s\n",
                 normalized_path);
    FREE_ERROR(err);
    return NO_SEVERE_ERROR;
  }

  color_printf(COLOR_INFO, "Pulling: %s\n", normalized_path);

  git_status_t git_status;
  /* Life time of git_status is same as normalized_path. */
  git_status.path = normalized_path;

  /* For any `git_read` failure, we just log them. return value is zero. */
  if (SUCCEEDED(err = git_read(&git_status))) {
    color_print(COLOR_SUCCESS, "Success.\n");
  } else {
    color_printf(COLOR_ERROR, "Error: %s\n  Repo at: %s\n", err->err_msg,
                 normalized_path);
  }

  FREE_ERROR(err);
  return NO_SEVERE_ERROR;
}

int main() {
  char* repos[] = {
      "~/Workspace/dotfiles",
      "~/Workspace/vimrc",
      "~/Workspace/mlvm",
      "~/Workspace/dockerfiles",
      "~/Workspace/notes",
  };

  int repo_count = sizeof(repos) / sizeof(char*);
  int i;

  for (i = 0; i < repo_count; ++i) {
    if (handle_repo(repos[i]) != NO_SEVERE_ERROR) return -1;
  }

  return 0;
}
