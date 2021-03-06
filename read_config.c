/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Local Headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */

#define filename_flush(x) char_flush(x, PATH_MAX)

/* ------------------------------------------------------------------------- */

static void replace_newline_with_null(char a[]){
  int i;
  for(i=0; i<PATH_MAX; i++){
    if(a[i] == '\n'){
      a[i] = '\0';
      if(a[i-1] == '/')
        a[i-1] = '\0';
    }
  }
}

/* ------------------------------------------------------------------------- */

/* Even though read_config.o will be linked with other object files,
 * below function will be visible to only and only read_config.o.
 * Using 'static' for this. 
 */
static void show_config(void){
  printf("\nSet Default Path for Questions as: %s",
         coff_config.quest_directory);
  printf("\nSet Default Path for Answers as:   %s",
         coff_config.test_directory);
  printf("\n----------------------------------------------------------------"
         "----------------\n");
}

/* ------------------------------------------------------------------------- */

void read_config(void){
  char file[PATH_MAX];
  char path[PATH_MAX];
  char temp[PATH_MAX];

  printf("\n"
         HIGHLIGHT_FORMAT
         BOLD_FORMAT
"                                                                            \
   \n"
"                               WELCOME TO COFF                              \
   \n"
"                                                                            \
   \n"
         NORMAL_FORMAT);

  printf("\n"
         BOLD_FORMAT
         "Reading configuration file."
         NORMAL_FORMAT);

  /* Get Home folder of the user */
  filename_flush(coff_config.home);
  strcpy(coff_config.home, getenv("HOME"));

  /* Get current working directory of the program */
  filename_flush(coff_config.cwd);
  getcwd(coff_config.cwd, PATH_MAX);

  filename_flush(file);
  strcpy(file, "~/.coff_config");
  expand_file_path(path, file);

  FILE *confile = fopen(path, "r");

  expand_dir_path(coff_config.null_directory, "~/coff/null");

  if(!confile){
    printf("\nConfig file \"~/.coff_config\" not found.");
    expand_dir_path(coff_config.quest_directory, "~/coff/quest");
    expand_dir_path(coff_config.test_directory, "~/coff/ans");
    show_config();
    return;
  }

  coff_config.quest_directory[0] = '-';
  coff_config.test_directory[0] = '-';

  while(1){
    fgets(temp, PATH_MAX, confile);
    if(feof(confile))
      break;
    replace_newline_with_null(temp);

    if(strcmp("PATH TO QUESTION", temp) == 0){
      filename_flush(temp);
      fgets(temp, PATH_MAX, confile);
      replace_newline_with_null(temp);
      
      filename_flush(path);
      filename_flush(coff_config.quest_directory);

      if(expand_dir_path(path, temp) != 0){
        expand_dir_path(coff_config.quest_directory, "~/coff/quest");
        continue;
      }

     strcpy(coff_config.quest_directory, path);
    }

    else if(strcmp("PATH TO ANSWER", temp) == 0){
      filename_flush(temp);
      fgets(temp, PATH_MAX, confile);
      replace_newline_with_null(temp);
      
      filename_flush(path);
      filename_flush(coff_config.test_directory);

      if(expand_dir_path(path, temp) != 0){
        expand_dir_path(coff_config.test_directory, "~/coff/ans");
        continue;
      }

     strcpy(coff_config.test_directory, path);
    }

    else
      continue;

  }

  fclose(confile);

  if(coff_config.quest_directory[0] == '-'){
    filename_flush(coff_config.quest_directory);
    expand_dir_path(coff_config.quest_directory, "~/coff/quest");
  }

  if(coff_config.test_directory[0] == '-'){
    filename_flush(coff_config.test_directory);
    expand_dir_path(coff_config.test_directory, "~/coff/ans");
  }

  show_config();

  return;
}
