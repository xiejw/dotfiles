#ifndef DOTFILES_C_COLOR_PRINT_H_
#define DOTFILES_C_COLOR_PRINT_H_

enum Color {
  COLOR_INFO = 36,    /* Cyan */
  COLOR_FYI = 33,     /* Yellow */
  COLOR_ERROR = 31,   /* Red */
  COLOR_SUCCESS = 32, /* Green */
};

/*
 * Prints the message with color. Flush is needed to ensure the color reset
 * applied in place immediately.
 *
 * Due to the limitation of variadic macro, if no argument is provided, use
 * `color_print`.
 */
#define color_printf(c, fmt, ...)                     \
  printf("\033[1;%dm" fmt "\033[0m", c, __VA_ARGS__); \
  fflush(stdout)

#define color_print(c, msg)              \
  printf("\033[1;%dm" msg "\033[0m", c); \
  fflush(stdout)

#endif
