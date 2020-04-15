#ifndef DOTFILES_C_ERROR_H_
#define DOTFILES_C_ERROR_H_

typedef int error_t;

#define OK 0
#define ENOT_PATH -1 /* Not a valid path. */
#define EGIT_PULL -2 /* Failure during git pull */
#define ETOO_MANY_RESULTS -3

#endif
