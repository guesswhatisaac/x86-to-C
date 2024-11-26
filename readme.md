# Dot Product Kernel (C and x86-64 Assembly Implementation)

This repository contains the implementation of a dot product kernel of two vectors using both C and x86-64 assembly. It compares the performance and correctness of both implementations.

## Files

- `main.c`:  
  This file contains the main program and handles memory allocation, initialization of vectors, and execution of both the C and Assembly implementations. It calls the helper functions for calculating the dot product, compares results, and measures execution time.

- `asmKernel.asm`:  
  The x86-64 assembly kernel that implements the dot product computation. It uses SIMD instructions to efficiently calculate the dot product of two vectors. The `dot_product_asm` function is the entry point for the assembly implementation and is called by the C code.
  
## Compilation and Linking Instructions

1. nasm -f elf64 -o asmKernel.o asmKernel.asm
2. gcc -std=c99 -c -o main.o main.c
3. gcc -std=c99 -o main.exe main.o asmKernel.o -lm
4. main.exe
                                           
#### FOR DEBUG MODE

3. gcc -g -std=c99 -o dot_product_debug.exe main.o asmKernel.o -lm
4. dot_product_debug.exe

#### FOR RELEASE MODE

3. gcc -O2 -std=c99 -o dot_product_release.exe main.o asmKernel.o  -lm
4. dot_product_release.exe

## Correctness Check

The dot product results from both the C and assembly implementations are compared to ensure correctness.

<img width="376" alt="image" src="https://github.com/user-attachments/assets/fb286bdc-bde6-4a3a-934e-2bce7098ae9b">

## Performance Analysis

The performance of the C and Assembly implementations can differ significantly. Here's a detailed comparison of the two kernels, with execution times measured by running each kernel at least 20 times to ensure accuracy.

### Comparing C and Assembly Kernels

- **Assembly Kernel**:
  - The **Assembly Kernel** can take full advantage of low-level optimizations, such as using SIMD instructions to process multiple data elements simultaneously. 

- **C Kernel**:
  - The **C Kernel**, while more portable and easier to maintain, does not typically exploit low-level hardware features as effectively as assembly code. 
  - While the **C Kernel** performs well in most cases, it is generally slower than the **Assembly Kernel** for computationally heavy operations like dot product calculations. This is because C code is higher-level, and compilers may not fully utilize the potential of the underlying hardware without extensive optimization hints.

### Debug Mode vs Release Mode

- **Debug Mode**:
  - Both the C and Assembly implementations will be slower in Debug Mode because optimizations are disabled. However, the Assembly implementation may still exhibit a slight performance advantage due to its direct use of lower-level instructions.
    
    <img width="335" alt="image" src="https://github.com/user-attachments/assets/2720f030-d20b-4269-accc-aa900503707c">


- **Release Mode**:
  - When compiled in Release Mode, the **Assembly Kernel** will likely show the fastest performance due to highly optimized SIMD instructions and minimal overhead. The **C Kernel** will still be faster than Debug Mode, but it may not be able to achieve the same level of performance as the assembly implementation because it cannot exploit low-level optimizations in the same way.
    
    <img width="333" alt="image" src="https://github.com/user-attachments/assets/01dbec58-b219-4320-bbc9-aaebe1bf25aa">

