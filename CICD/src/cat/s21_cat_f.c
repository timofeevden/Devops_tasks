#include <stdio.h>
#include <string.h>

#include "./s21_cat.h"

void No_Arg(struct str_flags *flags) {
  char symbol = 0, symbol_old = symbol;
  int line = 0;
  int s_was = 0;

  while (!feof(stdin)) {
    symbol = getc(stdin);
    UseFlags(&symbol, &symbol_old, flags, &line, &s_was);
    symbol_old = symbol;
  }
}

void S21_Cat(struct str_flags *flags, FILE *filename) {
  char symbol = 0, symbol_old = symbol;
  int line = 0;
  int s_was = 0;

  while (!feof(filename) && !ferror(filename)) {
    symbol = getc(filename);
    if (!feof(filename)) {
      if (flags->check == 1) {
        UseFlags(&symbol, &symbol_old, flags, &line, &s_was);
      } else {
        printf("%c", symbol);
      }
    }  //  symbol != EOF
    symbol_old = symbol;
  }
}

void UseFlags(char *symbol, char const *symbol_old, struct str_flags *flags_f,
              int *line, int *s_was) {
  if (flags_f->n == 1 && (*line) == 0) {
    printf("%6d\t", ++(*line));  //  нумерация всех строк
  }
  if (flags_f->n == 1 && *symbol_old == '\n' && flags_f->b != 1) {
    if (flags_f->s == 1 && *symbol == '\n') {
      if (*s_was == 0) {
        printf("%6d\t", ++(*line));
        if (flags_f->e == 1) printf("$");
        printf("\n");
      }
      *s_was = 1;  //  сжим пустых строк
    } else {
      printf("%6d\t", ++(*line));  //  нумерация всех строк
    }
  }
  if (flags_f->b == 1 && *symbol != '\n' && (*line) == 0) {
    printf("%6d\t", ++(*line));  //  нумерация непустых строк
  }
  if (flags_f->b == 1 && *symbol_old == '\n' && *symbol != '\n') {
    printf("%6d\t", ++(*line));  //  нумерация непустых строк
  }
  if (flags_f->s == 1 && *symbol_old == '\n' && *symbol == '\n') {
    if (*s_was == 0) {
      if (flags_f->e == 1) printf("$");
      printf("\n");
    }
    *s_was = 1;  //  сжим пустых строк
  } else if (flags_f->t == 1 && *symbol == '\t') {
    printf("^I");  //  табы
  } else if (flags_f->e == 1 && *symbol == '\n') {
    printf("$\n");  //  перенос $
  } else if (flags_f->v == 1 &&
             ((*symbol >= 0 && *symbol < 32) || *symbol == 127)) {
    printf("%s", NoPrintSymbols(*symbol));  //  невидимые символы
  } else {
    *s_was = 0;
    printf("%c", *symbol);
  }
}

char const *NoPrintSymbols(int c) {
  if (c == 127) c = 33;
  char const *no_print_symbols[] = {
      "^@", "^A", "^B", "^C", "^D",  "^E", "^F", "^G", "^H", "\t", "\n", "^K",
      "^L", "^M", "^N", "^O", "^P",  "^Q", "^R", "^S", "^T", "^U", "^V", "^W",
      "^X", "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_", " ",  "^?"};

  return no_print_symbols[c];
}

void Check_All_Flags(struct str_flags *flags2, char *argument, int *error) {
  if (strcmp("--number", argument) == 0) {
    flags2->n = 1;
  } else if (strcmp("--squeeze-blank", argument) == 0) {
    flags2->s = 1;
  } else if (strcmp("--number-nonblank", argument) == 0) {
    flags2->b = 1;
  } else {
    for (int j = 1; argument[j] != '\0'; j++) {
      if (argument[j] == 't' || argument[j] == 'T' || argument[j] == 'v' ||
          argument[j] == 'e' || argument[j] == 'E' || argument[j] == 's' ||
          argument[j] == 'b' || argument[j] == 'n') {
        if (argument[j] == 't' || argument[j] == 'T') flags2->t = 1;
        if (argument[j] == 'e' || argument[j] == 'E') flags2->e = 1;
        if (argument[j] == 's') flags2->s = 1;
        if (argument[j] == 'b') flags2->b = 1;
        if (argument[j] == 'n') flags2->n = 1;
        if (argument[j] == 'v') flags2->v = 1;
      } else {
        fprintf(
            stderr,
            "s21_cat: illegal option -- %c\nusage: s21_cat [-benstv] [file]...",
            argument[j]);
        *error = 1;
        break;
      }
    }
    if (flags2->t == 1 || flags2->e == 1) flags2->v = 1;
  }
}
