/* 
 * Physical memory (OS boot)
 *
+----------------------------+ 0xFFFFFFFF (4GB)
| Firmware (BIOS/UEFI)       |
| PCI/MMIO (Hardware Mapped) |
+----------------------------+
| OS Kernel (Loaded High)     | ← e.g., 0x100000 (1MB)
+----------------------------+
| Bootloader (Stage 2)        | ← e.g., 0x8000
+----------------------------+
| Boot Sector (0x7C00–0x7E00)| ← Loaded by BIOS
+----------------------------+
| Real-Mode IVT, BDA         | ← 0x0000–0x07FF
+----------------------------+ 0x00000000
*
*
*/

/*
 * Virtual Memory (Post-Boot, x86-64 Linux Example
 *
+----------------------------+ 0x7FFFFFFFFFFF (User Space Max)
| Stack (Grows ↓)            | ← e.g., 0x7ffde000
+----------------------------+
| Shared Libraries           | ← libc, etc.
+----------------------------+
| Heap (Grows ↑)             | ← malloc(), brk()
+----------------------------+
| .bss (Uninitialized Data)  |
+----------------------------+
| .data (Initialized Data)   |
+----------------------------+
| .text (Program Code)       | ← 0x400000 (Entry Point)
+----------------------------+ 0x000000000000
| Kernel Space (Inaccessible)| ← 0xffff800000000000+
+----------------------------+
*
*
*/

/*
 * Program Memory Layout
 *
+----------------------------+ High Addresses
| Environment Variables, Args|
+----------------------------+
| Stack (Local Variables)    | ↓ Grows downward
|   - Function call frames   |
|   - Return addresses       |
+----------------------------+
| (Unmapped Memory Guard)    | ← Prevents overflow
+----------------------------+
| Heap (Dynamic Memory)      | ↑ Grows upward
|   - malloc(), brk(), sbrk()|
+----------------------------+
| .bss (Uninitialized Data)  | ← Zero-initialized
+----------------------------+
| .data (Initialized Data)   | ← Global/static vars
+----------------------------+
| .text (Executable Code)    | ← Machine instructions
+----------------------------+ Low Addresses
*
*
*/


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *start = sbrk(0);
    printf("Initial break: %p\n", start);

    // Request 4KB more heap
    void *request = start + 4096;
    if (brk(request) == -1) {
        perror("brk");
        return 1;
    }

    // Safe to use memory between [start, request)
    int *arr = (int *)start;
    arr[0] = 42;  // OK: Within allocated range
    printf("arr[0] = %d\n", arr[0]);
    arr[1023] = 100;    // OK: Last valid int in the block
    // arr[1024] = 200;    // **CRASH!** Accessed beyond allocated memory.
    printf("arr[1023] = %d\n", arr[1023]);

    // Reset break (optional)
    if (brk(start) == -1) {
        perror("brk reset");
        return 1;
    }

    return 0;
}
