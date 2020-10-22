#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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

int execCmd(char **cmd) {
  pid_t pid;
  int   mypipe[2];

  if (pipe(mypipe)) {
    fprintf(stderr, "Pipe failed.\n");
    return -1;
  }

  /* Create the child process. */
  pid = fork();
  if (pid == (pid_t)0) {
    /* This is the child process.  Close the reading end first. */
    close(mypipe[0]);
    dup2(mypipe[1], 1);
    execvp(cmd[0], cmd);
    return 0;  // never reached.
  } else if (pid < (pid_t)0) {
    /* The fork failed. */
    fprintf(stderr, "Fork failed.\n");
    return -1;
  } else {
    /* This is the parent process.  Close writing end first. */
    close(mypipe[1]);
    return mypipe[0];
  }
}

int main(void) {
  char *args[] = {"ls", "-l", NULL};
  int   fd     = execCmd(args);
  read_from_pipe(fd);
}
