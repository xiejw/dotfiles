#ifndef DOTFILES_C_GIT_H_
#define DOTFILES_C_GIT_H_

typedef struct {
  char* path; /* set/own by owner */
} git_status_t;

int git_read(git_status_t* status) {
  printf("Read %s\n", status->path);
  return 0;
}

#endif
