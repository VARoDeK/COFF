#include <limits.h>

#ifndef __COFF_H__  /* COFF_H */

#define __COFF_H__

#define PATH_MAX_len PATH_MAX + 1

int print_err(const char[]);

/* Structure to contain defaily path of Question and Answers */
struct {
  char home[PATH_MAX_len];
  char quest_director[PATH_MAX_len];
  char test_directory[PATH_MAX_len];
}coff_config;

void filename_flush(char[]);
void read_config(void);
void expand_file_path(char[] /*dest*/, char[]/*source*/);
void expand_dir_path(char[] /*dest*/, char[]/*source*/);

#endif /* COOF_H */
