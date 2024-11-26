
// COMPILATION AND LINKING
nasm -f elf64 -o asmKernel.o asmKernel.asm
gcc -std=c99 -c -o main.o main.c
                                           

// FOR DEBUG
gcc -g -std=c99 -o dot_product_debug.exe main.o asmKernel.o -lm

// FOR RELEASE
gcc -O2 -std=c99 -o dot_product_release.exe main.o asmKernel.o  -lm


;;  gcc -std=c99 -o main.exe main.o asmKernel.o -lm