#!/bin/bash

DEPS="libboost-dev sphinx"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi

pip3 install sphinx_rtd_theme --break-system-packages