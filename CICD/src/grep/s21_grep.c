#include "./s21_grep_functions.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    fprintf(stderr, "usage: grep [options] template [file_name]\n");
  } else {
    char buf_from_file[4096], find_string[4096] = {'\0'};
    int flags_is_over = 0;
    int string_is_over = 0;
    int out_flag_string = 0;
    int cnt_files = 0;
    struct all_flags flag = {0};
    regex_t regex;

    //  сначала проверяем все флаги
    Checking_Flags(argc, argv, &out_flag_string, &flag, find_string,
                   &string_is_over, &cnt_files);
    flags_is_over = 1;
    // проверяем все файлы или искомую фразу
    for (int i = 1; i < argc; i++) {
      int check_ef_before = (argv[i - 1][0] == '-' &&
                             (argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' ||
                              argv[i - 1][strlen(argv[i - 1]) - 1] == 'e'));
      if (argv[i][0] != '-' && string_is_over == 1 && !check_ef_before) {
        ///  GREP
        Grep_21(argv[i], buf_from_file, find_string, &flag, &cnt_files, &regex);
      } else if (argv[i][0] != '-' && string_is_over == 0 && flags_is_over &&
                 flag.e == 0 && flag.f == 0) {
        Checking_String(find_string, argv[i], &string_is_over);
      }
    }  // for
  }

  return 0;
}

void Checking_Flags(int arg_cnt, char** arguments, int* out_flag_string,
                    struct all_flags* flags, char* find_string,
                    int* string_is_over, int* cnt_files) {
  for (int i = 1; i < arg_cnt; i++) {
    int check_ef_before =
        (arguments[i - 1][0] == '-' &&
         (arguments[i - 1][strlen(arguments[i - 1]) - 1] == 'f' ||
          arguments[i - 1][strlen(arguments[i - 1]) - 1] == 'e'));
    if (arguments[i][0] == '-' && !check_ef_before) {
      //    printf("Checking flags...\n");
      for (int j = 1; arguments[i][j] != '\0'; j++) {
        if (arguments[i][j] == 'e' || arguments[i][j] == 'i' ||
            arguments[i][j] == 'c' || arguments[i][j] == 'l' ||
            arguments[i][j] == 'v' || arguments[i][j] == 'n' ||
            arguments[i][j] == 'h' || arguments[i][j] == 's' ||
            arguments[i][j] == 'f' ||
            arguments[i][j] == 'o') {  // is it our symbol?
          if (arguments[i][j] == 's') {
            flags->s = 1;
          } else if (arguments[i][j] == 'i') {
            flags->i = 1;
          } else if (arguments[i][j] == 'h') {
            flags->h = 1;
          } else if (arguments[i][j] == 'o') {
            flags->o = 1;
          } else if (arguments[i][j] == 'v') {
            flags->v = 1;
          } else if (arguments[i][j] == 'n') {
            flags->n = 1;
          } else if (arguments[i][j] == 'l') {
            flags->l = 1;
          } else if (arguments[i][j] == 'c') {
            flags->c = 1;
          } else if (arguments[i][j] == 'f') {
            flags->f = 1;
            if (arguments[i][j + 1] == '\0') {
              *out_flag_string = i + 1;
              Checking_String_From_File(find_string, arguments[i + 1],
                                        string_is_over, flags);
            } else {
              char* end_f = &arguments[i][j] + 1;
              Checking_String_From_File(find_string, end_f, string_is_over,
                                        flags);
            }
            break;
          } else if (arguments[i][j] == 'e') {
            flags->e = 1;
            if (arguments[i][j + 1] == '\0') {
              *out_flag_string = i + 1;
              if (arguments[i + 1] != NULL)
                Checking_String(find_string, arguments[i + 1], string_is_over);
            } else {
              char* end_e = &arguments[i][j] + 1;
              Checking_String(find_string, end_e, string_is_over);
            }
            break;
          }
        } else if (flags->s == 0) {  // is it our symbol?
          fprintf(stderr, "grep: Invalid invalid option -- %c\n",
                  arguments[i][j]);
        }
      }  // for
    } else if (arguments[i][0] != '-' && !check_ef_before) {
      (*cnt_files)++;
    }
  }  //  for
  if (flags->f == 0 && flags->e == 0) (*cnt_files)--;
}

void Grep_21(char* argument, char* buf_from_file, char* find_string,
             struct all_flags* flags, int* cnt_files, regex_t* regex) {
  FILE* file = fopen(argument, "r");

  if (file != NULL) {
    int cnt = 0, line = 1, eflags = 0;
    eflags = REG_EXTENDED;

    if (flags->i == 1) eflags = REG_EXTENDED | REG_ICASE;
    regcomp(regex, find_string, eflags);

    while (!feof(file) && !ferror(file)) {
      regmatch_t pmatch[1];
      if (fgets(buf_from_file, 4096, file) != NULL) {
        int coincidence = regexec(regex, buf_from_file, 1, pmatch, 0);

        if (flags->v == 1) coincidence = !coincidence;
        if (coincidence == 0) cnt++;
        if (coincidence == 0 && flags->l == 0 && flags->c == 0) {
          if (flags->o == 0)
            Print_Search(flags, cnt_files, argument, buf_from_file, &cnt,
                         &line);
          else
            Use_Flag_O(flags, cnt_files, argument, buf_from_file, &cnt, &line,
                       regex, pmatch);
        }
        line++;
        if (feof(file) && coincidence == 0 &&
            buf_from_file[strlen(buf_from_file) - 1] != '\n' && flags->l == 0 &&
            flags->c == 0)
          printf("\n");
      }
    }  //  while

    if (flags->c == 1) {
      if ((*cnt_files) > 1 && flags->h == 0) printf("%s:", argument);
      if (flags->l == 1 && cnt > 1) {
        printf("1\n");
      } else {
        printf("%d\n", cnt);
      }
    }
    if (flags->l == 1 && cnt > 0) {
      printf("%s\n", argument);
    }

    regfree(regex);
    fclose(file);
  } else if (flags->s == 0) {
    fprintf(stderr, "grep: %s: No such file or directory\n", argument);
  }
}
