#ifndef DOTFILES_C_PATHS_H_
#define DOTFILES_C_PATHS_H_

#include <wordexp.h>
#include <string.h>

// Expands the `~` in the path.
//
// `dst` must be large enough to hold the result.
int expand_tilde_path(char* original_path, char* dst) {
  wordexp_t exp_result;
  if (wordexp(original_path, &exp_result, 0)) {
    return -1;
  }

  // The simpliest case: one output.
  if (exp_result.we_wordc != 1) {
    wordfree(&exp_result);
    return -2;
  }

  strcpy(dst, exp_result.we_wordv[0]);
  wordfree(&exp_result);
  return 0;
}

#endif
