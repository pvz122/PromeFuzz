#!/bin/bash

DEPS="libjpeg-turbo8-dev libjbig-dev libzstd-dev liblzma-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi