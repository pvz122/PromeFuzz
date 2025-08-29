#!/bin/bash

DEPS="groff flex bison libdbus-1-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi