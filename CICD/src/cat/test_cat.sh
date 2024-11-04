#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="127_symbols.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v
do
          TEST="$var $TEST_FILE"
          echo "$TEST"
          ./s21_cat $TEST > s21_cat.txt
          cat $TEST > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t -v
do
  for var2 in b e n s t v
  do
          TEST="$var$var2 $TEST_FILE"
          echo "$TEST"
          ./s21_cat $TEST > s21_cat.txt
          cat $TEST > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
      for var3 in -b -e -n -s -t -v
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST="$var $var2 $var3 $TEST_FILE"
          echo "$TEST"
          ./s21_cat $TEST > s21_cat.txt
          cat $TEST > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_cat.txt cat.txt

        fi
      done
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
      for var3 in -b -e -n -s -t -v
      do
          for var4 in -b -e -n -s -t -v
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST"
              ./s21_cat $TEST > s21_cat.txt
              cat $TEST > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                else
                  echo "$TEST" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm s21_cat.txt cat.txt

            fi
          done
      done
  done
done

F_TEST="-benstv $TEST_FILE"
echo "$F_TEST"
./s21_cat $F_TEST > s21_cat.txt
cat $F_TEST > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
    then
    (( COUNTER_SUCCESS++ ))
else
    echo "$F_TEST" >> log.txt
    (( COUNTER_FAIL++ ))
fi
rm s21_cat.txt cat.txt

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

if [ $COUNTER_FAIL -ne 0 ] || [ $COUNTER_SUCCESS -eq 0 ]
  then
    exit 100
fi
