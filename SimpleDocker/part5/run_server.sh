#!/bin/bash

gcc main.c -o miniserver -lfcgi
chmod 777 ./miniserver
nginx
nginx -g "daemon off;"
spawn-fcgi -p 8080 -n miniserver
nginx -s reload
tail -f /dev/null