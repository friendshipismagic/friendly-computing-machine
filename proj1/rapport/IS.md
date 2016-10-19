Instruction set for friendly computing processor
================================================

# OP Code signification

cf. graph (unidan?)

We use language prefix to economize instruction length

# R-type instructions

R-type Instruction takes content of input reg addr 1 and input reg addr 2,
applies some arithmetical operation to them and store the result to output 
register.

|---------+----------------------+------------------+------------------|
| OP Code | output register addr | input reg addr 1 | input reg addr 2 |
|---------+----------------------+------------------+------------------|
| 7 bits  | 3 bits               | 3 bits           | 3 bits           |
|---------+----------------------+------------------+------------------|

|---------+------+---------------------------------|
| Op Code | ASM  | Short Description               |
|---------+------+---------------------------------|
| 0000000 | NOP  | Don't do anything               |
| 0000011 | ADD  | Adds two signed numbers         |
| 0000111 | ADDU | Adds two unsigned numbers       |
| 0000010 | SUB  | Substracts signed numbers       |
| 0000110 | SUBU | Substracts unsigned numbers     |
| 0000100 | MULU | Multiplies two unsigned numbers |
|---------+------+---------------------------------|

# I-type instructions

|---------+----------------------+-----------------|
| OP Code | output register addr | immediate value |
|---------+----------------------+-----------------|
| 2 bits  | 3 bits               | 11 bits         |
|---------+----------------------+-----------------|

|---------+-------+----------------------------------------------------------------|
| Op Code | ASM   | Short Description                                              |
|---------+-------+----------------------------------------------------------------|
| 10      | ADDIU | Adds-accumulate an unsigned immediate value to output register |
| 11      | LWI   | Loads an immediate word                                        |
|---------+-------+----------------------------------------------------------------|

## ADDIU

Takes an immediate value, and adds it to the output register content, then store
it to output register.

## LWI

Sets the output register to immediate value.

# J-type instructions

Memory type instructions. Moves data from/to register to/from memory.

|---------+---------------+-------------|
| OP Code | register addr | memory addr |
|---------+---------------+-------------|
| 4 bits  | 3 bits        | 9 bits      |
|---------+---------------+-------------|

|---------+-----+-------------------|
| Op Code | ASM | Short Description |
|---------+-----+-------------------|
| 0010    | LW  | Loads a word      |
| 0011    | SW  | Stores a word     |
|---------+-----+-------------------|

# K-type instructions

Branch-type instructions. Branches to (current address + register pseudo addr)
based on input registers arithmetical comparison.

|---------+----------------------+------------------+------------------|
| OP Code | register pseudo addr | input reg addr 1 | input reg addr 2 |
|---------+----------------------+------------------+------------------|
| 2 bits  | 8 Bits               | 3 bits           | 3 bits           |
|---------+----------------------+------------------+------------------|

|---------+-----+---------------------------------------------------------------|
| OP Code | ASM | Short Description                                             |
|---------+-----+---------------------------------------------------------------|
| 01      | BNE | Branch to register Pseudo address if input regs are not equal |
|---------+-----+---------------------------------------------------------------|

