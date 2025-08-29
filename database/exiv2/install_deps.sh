#!/bin/bash

DEPS="libinih-dev doxygen graphviz libfmt-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi