#ifndef EXEC_H
#define EXEC_H

#include <sys/types.h>  // pid_t
#include <unistd.h>

#include "c/error.h"

// ----------------------------------------------------------------------------
// Prototype.
// ----------------------------------------------------------------------------

int execCmd(char **cmd);

// ----------------------------------------------------------------------------
// Implementation.
// ----------------------------------------------------------------------------

// Must be a NULL-terminated string list.
int execCmd(char **cmd) {
  int mypipe[2];
  if (pipe(mypipe)) return EPIPEFAIL;

  pid_t pid = fork();
  if (pid == (pid_t)0) {
    // This is the child process. Close the reading end.
    close(mypipe[0]);
    dup2(mypipe[1], STDOUT_FILENO);
    execvp(cmd[0], cmd);
    return 0;  // never reached.
  } else if (pid < (pid_t)0) {
    return EFORKFAIL;
  } else {
    // This is the parent process.  Close writing end first.
    close(mypipe[1]);
    return mypipe[0];
  }
}

#endif
