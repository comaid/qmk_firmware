#!/bin/bash
make -r -R -C ./ -f build_keyboard.mk  KEYBOARD=crkbd/rev1 KEYMAP=comaid SILENT=false $*
