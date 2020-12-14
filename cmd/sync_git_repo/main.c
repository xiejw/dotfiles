#include <stdio.h>
#include <unistd.h>

#include "c/color_print.h"
#include "c/constants.h"
#include "c/git.h"
#include "c/path.h"
#include "c/read_config_file.h"

// ----------------------------------------------------------------------------
// Prototype.
// ----------------------------------------------------------------------------

#define MAX_REPO_COUNT 50

error_t gitPullRepos(char** repo_list, int repo_count);
void    freeRepoList(char** repos, int repo_count);

int main() {
  {
    // ----------------------------------------
    // A golden list of repos for all machines.
    // ----------------------------------------
    char* repos[] = {
        /* clang-format off */
        "~/Workspace/vimrc",
        "~/Workspace/dotfiles",
        "~/Workspace/dockerfiles",
        "~/Workspace/notes",
        "~/Workspace/mlvm",
        "~/Workspace/eva",
        "~/Workspace/dsa",
        "~/Workspace/fsx",
        "~/Workspace/games",
        /* clang-format on */
    };

    int repo_count = sizeof(repos) / sizeof(char*);
    if (OK != gitPullRepos(repos, repo_count)) return EUNSPECIFIED;
  }
  {
    // ----------------------------------------
    // A customized list of repos for local.
    // ----------------------------------------
    char** repos = NULL;
    int    repo_count;
    if (OK != readRepoListFromConfig("~/.git_repo_list", &repos, &repo_count,
                                     MAX_REPO_COUNT))
      return EUNSPECIFIED;

    if (OK != gitPullRepos(repos, repo_count)) return EUNSPECIFIED;
    freeRepoList(repos, repo_count);
  }

  return OK;
}

// ----------------------------------------------------------------------------
// Implementation.
// ----------------------------------------------------------------------------

// Invokes git pull for the repo @ `path`.
error_t gitPull(char* path) {
  // ---------------------------------------------------------------------------
  // Step 1: normalize the git repository path.
  char normalized_path[MAX_PATH_LEN];
  if (OK != expand_tilde_path(path, normalized_path)) {
    cPrintf(COLOR_ERROR, "Error: not a valid path\n  Repo at: %s\n", path);
    return EUNSPECIFIED;
  }

  // Note: After this point, all errors are not end-of-world. So, log an error
  // to alert user and  move on (return OK).

  // ---------------------------------------------------------------------------
  // Step 2: check existence and permission.
  if (OK != access(normalized_path, F_OK)) {
    cPrintf(COLOR_FYI, "Skip repository as not existed\n  Repo at: %s\n",
            normalized_path);
    return OK;
  }

  // ---------------------------------------------------------------------------
  // Step 3: pull repository.
  cPrintf(COLOR_INFO, "Pulling: %s\n", normalized_path);

  git_status_t status;
  status.path = normalized_path;  // Lifetime s same as normalized_path.

  if (OK == gitReadStatus(&status)) {
    cPrint(COLOR_SUCCESS, "Success.\n");
  } else {
    cPrintf(COLOR_ERROR, "Error: failed to pull the git repo.\n  Repo at: %s\n",
            normalized_path);
  }

  return OK;
}

/* Takes actions on a list of git repositories.  */
error_t gitPullRepos(char** repo_list, int repo_count) {
  for (int i = 0; i < repo_count; ++i) {
    if (OK != gitPull(repo_list[i])) return EUNSPECIFIED;
  }
  return OK;
}

void freeRepoList(char** repos, int repo_count) {
  for (int i = 0; i < repo_count; i++) free(repos[i]);
  free(repos);
}
