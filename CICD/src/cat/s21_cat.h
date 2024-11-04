#ifndef S21_CAT_H_INCLUDED
#define S21_CAT_H_INCLUDED
#include <stdio.h>
#include <string.h>

struct str_flags {
  int check;
  int t, e, s, b, n, v;
};

void S21_Cat(struct str_flags *flags, FILE *filename);
void Check_All_Flags(struct str_flags *flags2, char *argument, int *error);
void UseFlags(char *symbol, char const *symbol_old, struct str_flags *flags_f,
              int *line, int *s_was);
void No_Arg(struct str_flags *flags);
char const *NoPrintSymbols(int c);

#endif  // S21_CAT_H_INCLUDED
