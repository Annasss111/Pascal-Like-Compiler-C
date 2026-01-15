# Mini-Compiler in C 🚀

A robust compiler developed in **C** for a Pascal-like procedural language. This project implements the full compilation pipeline from lexical analysis to intermediate code generation.

## 📋 Features

- **Lexical Analysis:** Tokenizes source code, handling identifiers, keywords, and operators.
- **Symbol Table:** Uses hashing/linked lists to manage variables and types.
- **Syntax Analysis:** Implements a **Recursive Descent Parser (LL1)** based on specific grammar rules.
- **Semantic Analysis:** Checks for type consistency (e.g., ensuring `int` isn't assigned to `char`).
- **Code Generation:** Outputs intermediate code for an abstract stack machine.

## 🛠️ Tech Stack

- **Language:** C (Standard C99)
- **Concepts:** Recursion, Pointers, Data Structures, Automata Theory.

## 📂 Project Structure

- `src/`: Contains all source code (`.c`) and header files (`.h`).
- `tests/`: Example source files to test the compiler.
- `docs/`: Project requirements and grammar specifications.

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/Pascal-Like-Compiler-C.git
