
// COMPILATION AND LINKING
nasm -f elf64 -o asmKernel.o asmKernel.asm
gcc -std=c99 -c -o main.o main.c
gcc -std=c99 -o main.exe main.o asmKernel.o -lm