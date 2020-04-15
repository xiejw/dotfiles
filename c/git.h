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
 *   - OK, ENOTPATH, EGITPULL.
 */
error_t git_read(git_status_t* status) {
  char* const path = status->path;

  if (OK != chdir(path)) {
    return ENOTPATH;
  }

  if (OK != system("git pull --rebase")) {
    return EGITPULL;
  }

  return OK;
}

#endif
