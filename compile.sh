#/usr/bin/bash

gcc main.c $(pkg-config --cflags --libs sdl3)
