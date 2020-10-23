#include <stdio.h>
#include <stdlib.h>

#include "c/exec.h"

/* Read characters from the pipe and echo them to stdout. */

void read_from_pipe(int file) {
  FILE *stream;
  int   c;
  stream = fdopen(file, "r");
  while ((c = fgetc(stream)) != EOF) {
    putchar(c);
  }
  fclose(stream);
}

int main(void) {
  char *args[] = {"ls", "-l", NULL};
  int   fd     = execCmd(args);
  read_from_pipe(fd);
}
