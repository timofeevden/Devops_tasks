#include "./s21_grep_functions.h"

void Checking_String(char* find_string, char* arg_str, int* string_is_over) {
  *string_is_over = 1;

  if (find_string[0] != '\0') strcat(find_string, "|");
  strcat(find_string, arg_str);
}

void Checking_String_From_File(char* find_string, char* file_name,
                               int* string_is_over, struct all_flags* flags) {
  FILE* file_strings = fopen(file_name, "r");
  *string_is_over = 1;

  if (file_strings != NULL) {
    while (!feof(file_strings) && !ferror(file_strings)) {
      char str_ff[4096];
      fgets(str_ff, 4096, file_strings);

      if (find_string[0] != '\0') {
        strcat(find_string, "|");
      }
      if (str_ff[strlen(str_ff) - 1] == '\n') str_ff[strlen(str_ff) - 1] = '\0';
      strcat(find_string, str_ff);
    }
    fclose(file_strings);
  } else if (flags->s == 0) {
    fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
  }
}

void Print_Search(struct all_flags* flags, int const* cnt_files, char* argument,
                  char* buf_from_file, int const* cnt, int* line) {
  if (flags->l == 1 && cnt != 0 && flags->h == 0) printf("%s\n", argument);
  if (flags->l == 0 && (*cnt_files) > 1 && flags->h == 0)
    printf("%s:", argument);
  if (flags->n == 1) printf("%d:", *line);
  if (flags->c == 0 && flags->l == 0 && flags->o == 0)
    printf("%s", buf_from_file);
}

void Use_Flag_O(struct all_flags* flags, int* cnt_files, char* argument,
                char* buf_from_file, int* cnt, int* line, regex_t* regex,
                regmatch_t* pmatch) {
  char* ptr = buf_from_file;

  Print_Search(flags, cnt_files, argument, buf_from_file, cnt, line);

  for (int i = 0;; i++) {
    if (regexec(regex, ptr, 1, pmatch, 0)) {
      if (flags->v == 1) printf("%s", ptr);
      break;
    }
    int len = (int)pmatch[0].rm_eo - (int)pmatch[0].rm_so;

    if (flags->v == 0) {
      printf("%.*s\n", len, ptr + pmatch[0].rm_so);
      ptr += pmatch[0].rm_eo;
    } else if (flags->v == 1) {
      while (ptr - buf_from_file < (int)pmatch[0].rm_so) printf("%c", *ptr++);

      ptr += len;
    }
  }
}
