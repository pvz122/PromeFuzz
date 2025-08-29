#!/bin/bash

DEPS="autoconf libtool libyaml-dev"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi