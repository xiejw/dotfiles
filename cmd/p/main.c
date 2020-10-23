#include "c/color_print.h"
#include "c/constants.h"
#include "c/exec.h"
#include "c/file_reader.h"

// ----------------------------------------------------------------------------
// Prototype.
// ----------------------------------------------------------------------------

int vimRunInBg();
int gitPending();

int main(void) {
  if (vimRunInBg()) {
    cPrint(COLOR_ERROR, "v\n");
  } else {
    cPrint(COLOR_ERROR, "vn\n");
  }

  if (gitPending()) {
    cPrint(COLOR_ERROR, "g\n");
  } else {
    cPrint(COLOR_ERROR, "gn\n");
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

  int  result = 0;
  char line[MAX_STR_LINE_LEN];
  while (1) {
    int len = frNextLine(handle, line);
    if (len == 0) break;

    if (strstr(line, "vim") != NULL) {
      result = 1;
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

  int  result = 0;
  char line[MAX_STR_LINE_LEN];
  // read oneline is enough.
  int len = frNextLine(handle, line);
  if (len > 0) {
    result = 1;
  }
  frClose(handle);
  return result;
}
