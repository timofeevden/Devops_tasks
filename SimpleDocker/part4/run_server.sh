#!/bin/bash

gcc main.c -o miniserver -lfcgi
service nginx start
spawn-fcgi -p 8080 -n miniserver
nginx -s reload
nginx -g "daemon off;"
tail -f /dev/null