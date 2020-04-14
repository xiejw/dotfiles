#ifndef DOTFILES_C_ERROR_H_
#define DOTFILES_C_ERROR_H_

typedef struct {
  char* err_msg; /* error message, must point to static message char array. */
} error_t;

#define SUCCEEDED(x) (NULL != (x))

#define OK() NULL

error_t* ERROR(char* static_error_message) {
  error_t* err = (error_t*)malloc(sizeof(error_t));
  err->err_msg = static_error_message;
  return err;
}

#define DECLARE_ERROR(err) error_t* err = NULL

#define FREE_ERROR(err) (err != NULL ? free(err) : (void*)(err))

#endif
