#ifndef DOTFILES_C_FILEREADER_H_
#define DOTFILES_C_FILEREADER_H_

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "c/error.h"

/* Byte size to read file block. */
static unsigned int max_buffer_size_ = 4096 * 16;

static unsigned int max_line_len_ = 500;

/* Opaque handle for line reading. */
typedef struct {
  /* Internal fields. */
  int fd_;
  unsigned char* buffer_;
  char end_of_file_;

  ssize_t pos_;
  ssize_t allocated_;
} fr_handle_t;

static error_t fr_load_next_buffer(fr_handle_t* handle) {
  handle->pos_ = 0L;
  handle->allocated_ = read(handle->fd_, handle->buffer_, max_buffer_size_);

  if (handle->allocated_ == -1) return EREADFILE;

  return OK;
}

error_t fr_open(fr_handle_t** handle, char* path) {
  int fd = open(path, O_RDONLY);
  if (fd == -1) {
    return EOPENFILE;
  }

  /* Allocate resources. */
  *handle = malloc(sizeof(fr_handle_t));
  (*handle)->buffer_ = malloc(max_buffer_size_ * sizeof(unsigned char));

  (*handle)->fd_ = fd;
  (*handle)->end_of_file_ = 0;
  (*handle)->pos_ = 0;
  (*handle)->allocated_ = 0;
  return OK;
}

void fr_close(fr_handle_t* handle) {
  close(handle->fd_);
  free(handle->buffer_);
  free(handle);
}

/*
 * Returns the size of the characters read.
 *
 * Args:
 *   - line should be free after succeed.
 *
 * Returns:
 *   - 0 end of file.
 *   - postive number.
 *   - -1 error
 */
int fr_next_line(fr_handle_t* handle, char* dst) {
  /* Allocates the buffer for current line. It is 1 larger than the
   * max_line_len_.
   */
  unsigned char line[max_line_len_ + 1];
  int current_len = 0;
  int i;

  if (handle->end_of_file_) return 0;

  /*
   * The loop ends in any of the following condition.
   * 1. end of file.
   * 2. find a end-of-line.
   * 3. reach maximul line length limit.
   */
  for (;;) {
    if (handle->pos_ >= handle->allocated_) {
      error_t err = fr_load_next_buffer(handle);
      if (OK != err) return err;
    }

    /* Checks whether it is end-of-file. */
    if (handle->allocated_ == 0) {
      handle->end_of_file_ = 1;
      if (current_len == 0) {
        /*
         * If there is nothing left after the last end-of-line, we should not
         * produce this.
         */
        return 0;
      } else {
        line[current_len] = '\0';
        strcpy(dst, (const char*)line);
        return current_len;
      }
    }

    /* Tries to find end-of-line, i.e., `\n` */
    for (i = handle->pos_; i < handle->allocated_; ++i) {
      if (handle->buffer_[i] == '\n') {
        int length = i - handle->pos_;

        if (current_len + length >= max_line_len_) return ELINELEN;

        /* Move the data from line to handle buffer. */
        memcpy(line + current_len, handle->buffer_ + handle->pos_, length);
        current_len += length;
        handle->pos_ = i + 1;

        line[current_len] = '\0';
        strcpy(dst, (const char*)line);
        return current_len;
      }
    }

    /* We reach the end of the buffer. */
    int length = handle->allocated_ - handle->pos_;
    if (current_len + length >= max_line_len_) return ELINELEN;

    memcpy(line + current_len, handle->buffer_ + handle->pos_, length);
    current_len += length;
    handle->pos_ = handle->allocated_;
    /* next iteration. */
  }
}

#endif
