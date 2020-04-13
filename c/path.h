#ifndef DOTFILES_C_PATHS_H_
#define DOTFILES_C_PATHS_H_

#include <string.h>
#include <wordexp.h>

/*
 * Expands the `~` in the path.
 *
 * Args:
 *   - `dst` must be large enough to hold the result.
 *
 * Returns:
 *   0 for no error.
 */
int expand_tilde_path(char* original_path, char* dst) {
  wordexp_t exp_result;
  if (wordexp(original_path, &exp_result, /*flags=*/0)) return -1;

  /* Only the simpliest case is supported: one output. So error out for others.
   */
  if (exp_result.we_wordc != 1) {
    wordfree(&exp_result);
    return -2;
  }

  strcpy(dst, exp_result.we_wordv[0]);
  wordfree(&exp_result);
  return 0;
}

#endif
