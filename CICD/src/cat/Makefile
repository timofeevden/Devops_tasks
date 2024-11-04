all:

s21_cat: clean
	gcc -Wall -Wextra -Werror s21_cat_f.c s21_cat.c -o s21_cat
s21_grep: clean
	gcc -Wall -Wextra -Werror ../grep/s21_grep.c ../grep/s21_grep_functions.c -o ../grep/s21_grep
clean:
	rm -rf ./s21_cat
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
style:
	clang-format -style=google -n *.c
