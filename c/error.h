#ifndef DOTFILES_C_ERROR_H_
#define DOTFILES_C_ERROR_H_

typedef int error_t;

#define OK 0
#define ENOTPATH -1        /* Not a valid path. */
#define EGITPULL -2        /* Failure during git pull */
#define ETOOMANYRESULTS -3 /* Expect single result. */

#endif
