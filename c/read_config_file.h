#ifndef READ_CONFIG_FILE_H_
#define READ_CONFIG_FILE_H_

#include "c/constants.h"
#include "c/file_reader.h"
#include "c/path.h"

/* Reads the config file at `config_path`.
 *
 * The `repo list` will be filled by the local repository path.
 * Space will be allocated. The total number will be filled in `count`.
 *
 * Upon success, the repo_list should be freed by call site. The `max_count`
 * limits the maximum number of repo.
 */
error_t readRepoListFromConfig(char* config_path, char*** repo_list, int* count,
                               int max_count) {
  *count = 0;  // Set first to avoid accident exit path.

  // --------------------------------------------------------------------------
  // Step 1: normalize the git repository path.
  char normalized_path[MAX_PATH_LEN];
  if (OK != expand_tilde_path(config_path, normalized_path)) {
    cPrintf(COLOR_ERROR, "Error: not a valid path\n  Config File at: %s\n",
            config_path);
    return ENOTPATH;
  }

  // --------------------------------------------------------------------------
  // Step 2: check existence and permission. If the config file is not present,
  // just ignore it.
  if (OK != access(normalized_path, F_OK)) {
    cPrintf(COLOR_FYI, "Skip config file as not existed: %s\n",
            normalized_path);
    return OK;
  }

  // --------------------------------------------------------------------------
  // Step 3: read the file line by line.
  fr_handle_t* handle;
  if (OK != frOpen(&handle, normalized_path)) {
    cPrintf(COLOR_ERROR, "Failed to open config File at: %s\n",
            normalized_path);
    return EOPENFILE;
  }

  *repo_list = malloc(max_count * sizeof(char*));

  error_t err = OK;
  while ((*count) < max_count) {
    char* line = malloc(MAX_PATH_LEN);
    int   len  = frNextLine(handle, line);
    if (len == 0) {
      free(line);
      break;
    }

    if (len < 0) {
      cPrintf(COLOR_ERROR, "Failed to read config File at: %s\n",
              normalized_path);
      err = EREADFILE;
      free(line);
      break;
    }

    (*repo_list)[(*count)++] = line;
  };

  if (*count == max_count) {
    cPrintf(COLOR_ERROR, "Too many lines in config File at: %s\n",
            normalized_path);
    err = EUNSPECIFIED;
  }

  frClose(handle);
  return err;
}

#endif
