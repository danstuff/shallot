#!/bin/bash

printf "\nBuilding project...\n\n"
mkdir build/
cd build/
cmake ..
cmake --build .

printf "\nDebugging project...\n\n"
cd bin/
gdb --batch-silent -ex run shallot
