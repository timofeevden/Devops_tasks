all:
	
s21_cat: clean
	gcc -Wall -Wextra -Werror ../cat/s21_cat_f.c ../cat/s21_cat.c -o ../cat/s21_cat
s21_grep: clean
	gcc -Wall -Wextra -Werror s21_grep.c s21_grep_functions.c -o s21_grep
clean:
	rm -rf ./s21_grep
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
style:
	clang-format -style=google -n *.c
