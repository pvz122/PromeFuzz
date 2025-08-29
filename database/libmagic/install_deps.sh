#!/bin/bash

DEPS="groff liblzma-dev libzstd-dev zlib1g-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi