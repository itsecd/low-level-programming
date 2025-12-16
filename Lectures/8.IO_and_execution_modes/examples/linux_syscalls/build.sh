#! /bin/bash

nasm -f elf32 "x86-32.asm"
gcc -m32 -o x86-32.elf x86-32.o
echo "Built x86-32"
nasm -f elf64 "x86-64.asm"
gcc -no-pie -o x86-64.elf x86-64.o
echo "Built x86-64"
