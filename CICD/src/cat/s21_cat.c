//#include <stdio.h>
//#include <string.h>
#include "./s21_cat.h"

int main(int argc, char *argv[]) {
  struct str_flags flags = {0};

  if (argc == 1) {
    No_Arg(&flags);
  } else {
    FILE *filename = NULL;
    int error = 0;
    int flags_is_over = 0;

    for (int i = 1; i < argc && !error; i++) {
      if (argv[i][0] == '-' && !flags_is_over) {
        flags.check = 1;
        Check_All_Flags(&flags, argv[i], &error);
      } else {
        flags_is_over = 1;
        filename = fopen(argv[i], "r");

        if (NULL != filename) {
          S21_Cat(&flags, filename);
          fclose(filename);
          filename = NULL;
        } else {
          fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
        }
      }
    }  //  for
    if (flags_is_over == 0 && flags.check == 1 && !error) {
      No_Arg(&flags);
    }
  }
  return 0;
}
