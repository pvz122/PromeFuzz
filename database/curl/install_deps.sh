#!/bin/bash

DEPS="libpsl-dev libssl-dev libzstd-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi