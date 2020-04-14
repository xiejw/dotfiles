#ifndef DOTFILES_C_GIT_H_
#define DOTFILES_C_GIT_H_

#include <stdlib.h>
#include <unistd.h>

#include "c/error.h"

typedef struct {
  char* path; /* set/own by owner. */
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
error_t* git_read(git_status_t* status) {
  char* const path = status->path;

  if (0 != chdir(path)) {
    return ERROR("Failed to `cd` into the repository.");
  }

  if (0 != system("git pull --rebase")) {
    return ERROR("Failed to pull from remote git repository.");
  }

  return OK();
}

#endif
