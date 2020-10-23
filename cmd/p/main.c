#include "c/color_print.h"
#include "c/constants.h"
#include "c/exec.h"
#include "c/file_reader.h"

// ----------------------------------------------------------------------------
// Prototype.
// ----------------------------------------------------------------------------

#define YES 1
#define NO  0

int vimRunInBg();
int gitPending();
int gitBranceName(char*);

int main(void) {
  if (YES == vimRunInBg()) {
    cPrint(COLOR_ERROR, "v\n");
  } else {
    cPrint(COLOR_ERROR, "vn\n");
  }

  if (YES == gitPending()) {
    cPrint(COLOR_ERROR, "g\n");
  } else {
    cPrint(COLOR_ERROR, "gn\n");
  }

  char name[100];
  if (YES == gitBranceName(name)) {
    cPrintf(COLOR_ERROR, "b: %s\n", name);
  } else {
    cPrint(COLOR_ERROR, "bn\n");
  }
}

// ----------------------------------------------------------------------------
// Implementation.
// ----------------------------------------------------------------------------

int vimRunInBg() {
  char* args[] = {"ps", "-T", NULL};
  int   fd     = execCmd(args);

  fr_handle_t* handle;
  if (frDOpen(&handle, fd) != OK) {
    cPrint(COLOR_ERROR, "Error: failed to call ps");
    close(fd);
    return EUNSPECIFIED;
  }

  int  result = NO;
  char line[MAX_STR_LINE_LEN];
  while (1) {
    int len = frNextLine(handle, line);
    if (len == 0) break;

    if (strstr(line, "vim") != NULL) {
      result = YES;
      break;
    }
  }
  frClose(handle);
  return result;
}

int gitPending() {
  char* args[] = {"git", "status", "-s", NULL};
  int   fd     = execCmd(args);

  fr_handle_t* handle;
  if (frDOpen(&handle, fd) != OK) {
    cPrint(COLOR_ERROR, "Error: failed to call ps");
    close(fd);
    return EUNSPECIFIED;
  }

  int  result = NO;
  char line[MAX_STR_LINE_LEN];
  // read oneline is enough.
  int len = frNextLine(handle, line);
  if (len > 0) {
    result = YES;
  }
  frClose(handle);
  return result;
}

int gitBranceName(char* name) {
  char* args[] = {"git", "branch", "--no-color", NULL};
  int   fd     = execCmd(args);

  fr_handle_t* handle;
  if (frDOpen(&handle, fd) != OK) {
    cPrint(COLOR_ERROR, "Error: failed to call ps");
    close(fd);
    return EUNSPECIFIED;
  }

  int  result = NO;
  char line[MAX_STR_LINE_LEN];
  while (1) {
    int len = frNextLine(handle, line);
    if (len == 0) break;
    if (len < 3) continue;
    if (line[0] != '*') continue;
    strcpy(name, line + 2);
    result = YES;
    break;
  }
  frClose(handle);
  return result;
}
