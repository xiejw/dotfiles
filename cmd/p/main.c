#include "c/color_print.h"
#include "c/constants.h"
#include "c/exec.h"
#include "c/file_reader.h"

int main(void) {
  char* args[] = {"ps", "-T", NULL};
  int   fd     = execCmd(args);

  fr_handle_t* handle;
  if (frDOpen(&handle, fd) != OK) {
    cPrint(COLOR_ERROR, "Error: failed to call ps");
    return EUNSPECIFIED;
  }

  int  vim = 0;
  char line[MAX_PATH_LEN];
  while (1) {
    int len = frNextLine(handle, line);
    if (len == 0) break;

    if (strstr(line, "vim") != NULL) {
      vim = 1;
      break;
    }
  }
  if (vim) {
    cPrint(COLOR_ERROR, "yes");
  } else {
    cPrint(COLOR_ERROR, "no");
  }
  frClose(handle);
}
