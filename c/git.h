#ifndef DOTFILES_C_GIT_H_
#define DOTFILES_C_GIT_H_

#include <stdlib.h>
#include <unistd.h>

typedef struct {
  char* path; /* set/own by owner */
} git_status_t;

int git_read(git_status_t* status) {
  char* const path = status->path;
  printf("Read %s\n", path);

  if (0 != chdir(path)) return -1;

  if (0 != system("git pull --rebase")) return -2;

  return 0;
}

#endif
