#ifndef COLOR_PRINT_H_
#define COLOR_PRINT_H_

#include <stdio.h>

#define COLOR_RED    31
#define COLOR_GREEN  32
#define COLOR_YELLOW 33
#define COLOR_CYAN   36

enum Color {
  COLOR_INFO    = COLOR_CYAN,
  COLOR_FYI     = COLOR_YELLOW,
  COLOR_ERROR   = COLOR_RED,
  COLOR_SUCCESS = COLOR_GREEN,
};

/* Prints the message with color.
 *
 * Due to the limitation of variadic macro, if no argument is provided, use
 * `cPrint`.
 *
 *     cPrintf(COLOR_FYI, "Processing %s...\n", item_name);
 *     cPrint(COLOR_FYI, "Processing ...\n");
 *
 * Flush is needed to ensure the color reset applied in place immediately. */
#define cPrintf(c, fmt, ...)                          \
  printf("\033[1;%dm" fmt "\033[0m", c, __VA_ARGS__); \
  fflush(stdout)

#define cPrint(c, msg)                   \
  printf("\033[1;%dm" msg "\033[0m", c); \
  fflush(stdout)

#endif
