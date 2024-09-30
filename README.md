# 🚀 RISC-V Assembly to 32-bit Machine Code Converter

![RISC-V Logo](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bc/RISC-V-logo.png/600px-RISC-V-logo.png)

## 🛠 Project Overview

Welcome to **RISC-V Assembly to 32-bit Machine Code Converter**! This project is a **C++ program** that converts **RISC-V assembly code** into **32-bit machine code**. It supports various instruction formats like **R-type**, **I-type**, **B-type**, and **J-type**, making it a great resource for anyone looking to understand RISC-V architecture at a deeper level.

This tool can encode basic operations such as:
- **Addition** (`add`)
- **Subtraction** (`sub`)
- **Logical Operations** (`and`, `or`, `xor`)
- **Immediate Operations** (`addi`, `andi`, `ori`, `xori`)
- **Branching** (`beq`, `bne`, `blt`, `bge`)
- **Jumping** (`jal`, `jalr`)
- **Memory Access** (`lw`, `sw`, `lb`, `sb`)

## 🔑 Key Features

- **Supports RISC-V Instruction Set**: Handles R-type, I-type, B-type, and J-type instructions.
- **Instruction to Binary Encoding**: Converts human-readable assembly instructions into machine code.
- **Flexible Input**: Modify the input assembly lines in the `main()` function to test different instructions.
- **Readable Output**: Displays both the assembly code and its equivalent machine code.

## 🖥 Example Usage

Here’s a quick look at how the program processes assembly code and converts it to machine code:

```cpp
add x1, x2, x3     // R-type: Addition
sub x0, x1, x3     // R-type: Subtraction
```
```output
Assembly: add x1, x2, x3
Machine Code: 00000000001100010000000010110011

Assembly: sub x0, x1, x3
Machine Code: 01000000001100010000000010110011
```


## 🚀 Getting Started

### Prerequisites

To run this project, you'll need:

- A C++ compiler (e.g., `g++`, `clang++`)
- Basic understanding of RISC-V architecture

### Installation

1. Clone this repository:

```bash
git clone https://github.com/yourusername/risc-v-assembler.git
```
### Installation

1. Clone this repository:

    ```bash
    git clone https://github.com/yourusername/risc-v-assembler.git
    ```

2. Navigate to the project directory:

    ```bash
    cd risc-v-assembler
    ```

3. Compile the program:

    ```bash
    g++ -o risc_v_assembler main.cpp
    ```

4. Run the executable:

    ```bash
    ./risc_v_assembler
    ```
## 🌟 Contributing

Contributions are welcome! If you have suggestions for new features, improvements, or bug fixes, feel free to:

- Open an issue to discuss your ideas.
- Submit a pull request with your changes.
