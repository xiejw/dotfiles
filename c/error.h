#ifndef ERROR_H_
#define ERROR_H_

typedef int error_t;

#define OK              0
#define EUNSPECIFIED    -1  // An unspecified general error.
#define ENOTPATH        -2  // Not a valid path.
#define EGITPULL        -3  // Failure during git pull.
#define ETOOMANYRESULTS -4  // Expect single result.
#define EOPENFILE       -5  // Failure during opening file.
#define EREADFILE       -6  // Failure during reading file.
#define ELINELEN        -7  // Line is too long.
#define EPIPEFAIL       -8  // Pipe failed.
#define EFORKFAIL       -9  // Fork failed.

#endif
