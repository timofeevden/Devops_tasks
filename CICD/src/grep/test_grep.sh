#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="s21_grep.c"
echo "" > log.txt


for var1 in -i -v -c -l -n -h -o
do
    for var2 in a file str eof
    do
              TEST="$var1 $var2 $TEST_FILE"
              echo "$TEST"
              ./s21_grep $TEST > s21_grep.txt
              grep $TEST > grep.txt
              DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
              if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                else
                  echo "./s21_grep $TEST" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm s21_grep.txt grep.txt
    done
done

TEST="-e a -e b $TEST_FILE"
echo "$TEST"
./s21_grep $TEST > s21_grep.txt
grep $TEST > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
        echo "./s21_grep $TEST" >> log.txt
        (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

TEST="-f a.txt $TEST_FILE"
echo "$TEST"
./s21_grep $TEST > s21_grep.txt
grep $TEST > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
        echo "./s21_grep $TEST" >> log.txt
        (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

for var1 in -i -v -c -l -n -h -o
do
    for var2 in a file str eof
    do
        TEST=" $var1 $var2 -s $TEST_FILE"
        echo "$TEST"
        ./s21_grep $TEST > s21_grep.txt
        grep $TEST > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "./s21_grep $TEST" >> log.txt
                (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -ne 0 ] || [ $COUNTER_SUCCESS -eq 0 ]
  then
    exit 200
fi


