#!/bin/bash
mkdir -p build
gcc -o build/SimProc src/SimProc.c -Wall `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` -lm -lpthread -export-dynamic
