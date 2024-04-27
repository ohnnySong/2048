#!/bin/bash

# Compile the source file
gcc 2048game.c -o 2048game

# Move the executable to the "executable" directory
mkdir -p executable
mv 2048game ../executable/
rm 2048game
rm -r executable
echo "Compilation and moving executable completed."
