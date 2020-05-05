/* Standard headers */
#include <stdio.h>
#include <argp.h>

/* Local headers */
#include "coff.h"

/* ------------------------------------------------------------------------- */
/* ARGP definitions */

/* Version */
const char *argp_program_version = "coff - Offline Judge : 0.01";

/* Documentaion */
static const char usage_doc[] =
  "coff - Offline Judge";

/* A description of the arguments we accept. */
//static char args_doc[] = "show test lang quest";

/* The options we understand. */
static struct argp_option coff_options[] = {
  {"show",    's', "FILE",      0,  "Name of Question File" },
  {"test",    't', "FILE",      0,  "Name of your Program/ Solution File" },
  {"lang",    'l', "LANG",      0,  
  "Specify the language of your program. LANG=\n\
[C, C++, C++11, C++17, JAVA, Python2, Python3]\n" },
  {"quest",   'q', "FILE",      0,  "Name of Question File" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments{
  char *args[4];
  char *test_file;
  char *show_file;
  char *quest_file;
  char *lang;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state){
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */

//  if(state->argc == 1)
//    argp_usage(state);

  struct arguments *coff_arguments = state->input;
  
  switch (key){
    case 's':
      coff_arguments->show_file = arg;
      break;

    case 't':
      coff_arguments->test_file = arg;
      break;

    case 'l':
      coff_arguments->lang = arg;
      break;

    case 'q':
      coff_arguments->quest_file = arg;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp coff_argp = { coff_options, parse_opt, 0, usage_doc };
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
int main(int argc, char *argv[]){

  struct arguments coff_arguments;

  /* Default values. */
  coff_arguments.show_file = "-";
  coff_arguments.test_file = "-";
  coff_arguments.lang = "-";
  coff_arguments.quest_file = "-";

  if(argc == 1){
    fprintf(stderr,"coff: Too few arguments"
                   "\nTry `coff --help' or `coff --usage' for more information.\n");
    return 0;
  }

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&coff_argp, argc, argv, ARGP_NO_ARGS, 0, &coff_arguments);

  printf("\nTest Mode - Showing arguments");
  printf("\nShow = %s\nTest = %s\nLang = %s\nQuest = %s\n",
         coff_arguments.show_file,
         coff_arguments.test_file,
         coff_arguments.lang,
         coff_arguments.quest_file);

  return 0; 
}
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

