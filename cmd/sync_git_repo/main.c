#include <stdio.h>
#include <unistd.h>

#include "c/color_print.h"
#include "c/file_reader.h"
#include "c/git.h"
#include "c/path.h"

#define MAX_PATH_LEN   100
#define MAX_REPO_COUNT 50

/* Takes action on a single repo. */
error_t git_pull_repository(char* path) {
  /* Step 1: normalize the git repository path. */
  char normalized_path[MAX_PATH_LEN];
  if (OK != expand_tilde_path(path, normalized_path)) {
    color_printf(COLOR_ERROR, "Error: not a valid path\n  Repo at: %s\n", path);
    return EUNSPECIFIED;
  }

  /**********************************************************
   * Note: After this point, all errors are not end-of-world.
   * - log an error to alert user
   * - move on (return OK).
   */

  /* Step 2: check existence and permission. */
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
    color_printf(COLOR_ERROR,
                 "Error: failed to pull the git repo.\n  Repo at: %s\n",
                 normalized_path);
  }

  return OK;
}

/* Takes actions on a list of git repositories.  */
error_t git_pull_repository_list(char** repo_list, int repo_count) {
  int i;
  for (i = 0; i < repo_count; ++i) {
    if (OK != git_pull_repository(repo_list[i])) return EUNSPECIFIED;
  }
  return OK;
}

/*
 * Reads the config file at `config_path`. Each line is a repo list for local
 * host.
 *
 * The repo_list should be free via `free_repo_list` later.
 */
error_t read_repo_list_from_config_file(char* config_path, char*** repo_list,
                                        int* count, int max_count) {
  char normalized_path[MAX_PATH_LEN];
  if (OK != expand_tilde_path(config_path, normalized_path)) {
    color_printf(COLOR_ERROR, "Error: not a valid path\n  Config File at: %s\n",
                 config_path);
    return ENOTPATH;
  }

  /* If the config file is not present, just ignore it. */
  if (OK != access(normalized_path, F_OK)) {
    color_printf(COLOR_FYI, "Skip config file as not existed: %s\n",
                 normalized_path);
    *count = 0;
    return OK;
  }

  fr_handle_t* handle;
  if (OK != fr_open(&handle, normalized_path)) {
    color_printf(COLOR_ERROR, "Failed to open config File at: %s\n",
                 normalized_path);
    return EOPENFILE;
  }

  *count     = 0;
  *repo_list = malloc(max_count * sizeof(char*));

  error_t err = OK;
  while ((*count) < max_count) {
    char* line = malloc(MAX_PATH_LEN);
    int   len  = fr_next_line(handle, line);
    if (len == 0) {
      free(line);
      break;
    }

    if (len < 0) {
      color_printf(COLOR_ERROR, "Failed to read config File at: %s\n",
                   normalized_path);
      err = EREADFILE;
      free(line);
      break;
    }

    (*repo_list)[(*count)++] = line;
  };

  if (*count == max_count) {
    color_printf(COLOR_ERROR, "Too many lines in config File at: %s\n",
                 normalized_path);
    err = EUNSPECIFIED;
  }

  fr_close(handle);
  return err;
};

int main() {
  /* A golden list of repos for all machines. */
  {
    char* repos[] = {
        /* clang-format off */
        "~/Workspace/vimrc",
        "~/Workspace/dotfiles",
        "~/Workspace/dockerfiles",
        "~/Workspace/mlvm",
        "~/Workspace/fsx",
        "~/Workspace/notes",
        "~/Workspace/games",
        /* clang-format on */
    };

    int repo_count = sizeof(repos) / sizeof(char*);
    if (OK != git_pull_repository_list(repos, repo_count)) return EUNSPECIFIED;
  }

  /* A customized list of repos for local host. */
  {
    char** repos = NULL;
    int    repo_count;

    if (OK != read_repo_list_from_config_file("~/.git_repo_list", &repos,
                                              &repo_count, MAX_REPO_COUNT))
      return EUNSPECIFIED;

    if (OK != git_pull_repository_list(repos, repo_count)) return EUNSPECIFIED;

    { /* frees the repo_list. */
      int i;
      for (i = 0; i < repo_count; i++) free(repos[i]);
      free(repos);
    }
  }

  return OK;
}
