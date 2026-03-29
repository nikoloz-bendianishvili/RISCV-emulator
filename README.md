# RISC-V Assembly Emulator

A custom, lightweight RISC-V CPU emulator written in C++. This project was developed to demonstrate a deep understanding of computer architecture, instruction decoding, memory management, and low-level execution cycles. 

It reads raw RISC-V assembly files, parses the instructions, manages the CPU state (registers and memory), and executes the code accurately.

## 🚀 Key Features
* **Two-Pass Assembler:** Implements a two-pass parsing system in `main.cpp` to map labels to instruction lines, allowing for accurate forward and backward branching.
* **Core RV32I Support:** Simulates a 32-bit architecture, successfully executing arithmetic, bitwise, shift, memory, and branching instructions.
* **ABI Register Mapping:** Fully maps all standard RISC-V registers (e.g., `sp`, `ra`, `t0-t6`, `s0-s11`, `a0-a7`) to their respective hardware indices (`x0-x31`).
* **Byte-Addressable Memory:** Manages a continuous memory vector capable of handling stack operations and standard load/store (`lw`, `sw`) commands.
* **Custom Debug Directives:** Includes custom assembler directives (like `printf`, `endl`, and `bnefortests`) for integrated unit testing and output verification.

## 🗂️ Project Structure
* **`cpu.hpp` & `cpu.cpp`**: The core CPU class. Handles the datapath, memory allocation, string sanitization, and the massive execution block that emulates hardware instruction execution.
* **`main.cpp`**: The driver program. Handles file I/O, comment stripping, the two-pass label resolution, and the main Program Counter (PC) execution loop.
* **`test.asm`**: A comprehensive test suite written in assembly that verifies ALU operations, memory loops, and branch logic to ensure the emulator operates accurately.

## 🛠️ Supported Instructions (Subset)
* **Arithmetic & Logical:** `add`, `sub`, `addi`, `and`, `or`, `xor`, `andi`, `ori`, `xori`, `li`
* **Shifts:** `sll`, `srl`, `sra`, `slli`, `srli`, `srai`
* **Control Flow:** `beq`, `bne`, `blt`, `bge`, `bgtz`, `blez`
* **Memory Operations:** `lw`, `sw`
* **System/Pseudo:** `ecall` (exit code 10), `printf`, `endl`

## 💻 How to Compile and Run
To run the emulator locally, you will need a standard C++ compiler (like GCC or Clang). 

1. Clone the repository and navigate to the project folder.
2. Compile the source code:
```bash
g++ main.cpp cpu.cpp -o riscv_emulator
```

3. Run the compiled binary:
```bash
./riscv_emulator
```

*(Note: By default, the program looks for `test.asm` in the same directory to run its execution loop).*
