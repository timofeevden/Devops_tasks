#!/bin/bash

scp ./src/cat/s21_cat turkatrj@172.24.116.8:/home/turkatrj/
scp ./src/grep/s21_grep turkatrj@172.24.116.8:/home/turkatrj/
ssh turkatrj@172.24.116.8 "echo "1" | sudo -S mv s21_cat s21_grep /usr/local/bin/"
