#ifndef DOTFILES_C_GIT_H_
#define DOTFILES_C_GIT_H_

#include <stdlib.h>
#include <unistd.h>

typedef struct {
  char* path; /* set/own by owner. */
  char* err;  /* error message, filled by `git_read`. */
} git_status_t;

/*
 * Reads the repository status.
 *
 * For the provided `status`, `path` must be set by caller.
 *
 * Returns:
 *   0 if succeed; otherwise, `status->err` will be set. Error message is
 *   pointed to the static data in the binary.
 */
int git_read(git_status_t* status) {
  char* const path = status->path;

  if (0 != chdir(path)) {
    status->err = "Failed to `cd` into the repository.";
    return -1;
  }

  if (0 != system("git pull --rebase")) {
    status->err = "Failed to pull from remote.";
    return -2;
  }

  return 0;
}

#endif
