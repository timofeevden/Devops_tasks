#ifndef S21_GREP_FUNCTIONS_H_INCLUDDED
#define S21_GREP_FUNCTIONS_H_INCLUDDED
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

struct all_flags {
  int e, i, c, l, v, n, h, s, f, o;
};

void Checking_Flags(int arg_cnt, char** arguments, int* after_e_string,
                    struct all_flags* flags, char* find_string,
                    int* string_is_over, int* cnt_files);
void Checking_String(char* find_string, char* arg_str, int* string_is_over);
void Checking_String_From_File(char* find_string, char* file_name,
                               int* string_is_over, struct all_flags* flags);
void Grep_21(char* argv, char* buf_from_file, char* find_string,
             struct all_flags* flags, int* cnt_files, regex_t* regex);
void Print_Search(struct all_flags* flags, int const *cnt_files, char* argument,
                  char* buf_from_file, int const *cnt, int* line);
void Use_Flag_O(struct all_flags* flags, int* cnt_files, char* argument,
                char* buf_from_file, int* cnt, int* line, regex_t* regex,
                regmatch_t* pmatch);

#endif  //  S21_GREP_FUNCTIONS_H_INCLUDDED
