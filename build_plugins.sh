#!/bin/bash
#
# Build script to compile all plugins listed in $PLUGINS below
# 
# Derived from https://github.com/sgreg/dynamic-loading

PLUGINS="meike6.5f2.0 laowa4.0f2.8 ptgui11"

CXXFLAGS="-shared -fPIC -Wall -Wextra -DDCTL_PLUGIN -O2"

for plugin in $PLUGINS
do
    echo "Building plugin $plugin"
    g++ $CXXFLAGS -o $plugin.plugin $plugin.plugin.cpp
done
