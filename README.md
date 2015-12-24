# Compiler
Compiler and Optimizer for a custom language in C 

Project Description
The project consists of two main parts:
1. Complete the partially implemented recursive descent LL(1) parser that generates
ILOC instructions.
2. Write a dead-code eliminator that recognizes and deletes redundant, i.e., dead ILOC
instructions.

In addition, you are asked to write the PrintInstructionList routine. The project
represents an entire programming environment consisting of a compiler, an optimizer, and a
simulator (virtual machine) for ILOC. The ILOC simulator is called sim and will be made
available to you as an executable on the ilab machines. This will allow you to check for
correctness of your generated and optimized code.


Compiler
The recursive descent LL(1) parser implements a simple code generator. You should follow
the main structure of the code as given to you in file Compiler.c. As given to you, the
file contains code for function digit, variable, and partial code for function expr. As is,
the compiler is able to generate code only for expressions that contain “+” operations on
operands that are digits or the variable “f”. You will need to add code in the provided stubs
to generate correct RISC machine code for the entire program. Do not change the signatures
of the recursive functions. Note: The left-hand and right-hand occurrences of variables are
treated differently.


I/O Instruction Utility
Within the Optimizer, a sequence of ILOC instructions is represented as a doubly-linked
list. You are asked to implement the following utility function in file InstrUtils.c.
void PrintInstructionList(FILE *outfile, Instruction *instr);
Function PrintInstructionList traverses the instruction list beginning with instruction
”instr”. The list is written into file ”outfile”. The implementation of this function must be
based on the utility function
void PrintInstruction(FILE *outfile, Instruction *instr);
The implementation of the latter function is provided to you in file InstrUtils.c. This
is also the file that will contain your implementation of PrintInstructionList


Dead Code Elimination Optimization
The dead code elimination optimizer expect the input file to be provided at the standard
input (stdin), and will write the generated code back to standard output (stdout).
The basic algorithm identifies “crucial” instructions. The initial crucial instructions
are all outputAI instructions. For all outputAI instruction, the algorithm has to detect
all instructions that contribute to the value of the variable that is written out. The first
instruction that needs to be found is the one that stores the value into the variable that is
written out. This storeAI instruction is marked as critical and will reference a register and
R 0 . There will be instructions that compute a value for this register, which also need to be
marked as critical. This marking process terminates once no more instructions need to be
marked as critical. If this basic algorithm is performed for all outputAI instructions, the
instructions that were not marked critical can be deleted.
Instructions that are deleted as part of the optimization process have to be explicitly
deallocated using the C free command in order to avoid memory leaks. You will implement
your dead code eliminator pass in file Optimizer.c. All of your “helper” functions should
be implemented in this file.


ILOC Simulator
The virtual machine executes ILOC program. If a outputAI <id> instruction is executed,
the value of the specified memory location is written to standard output (stdout). All values
are of type integer. An ILOC simulator is provided as an executable (sim). The ILOC
simulator reports the overall number of executed instructions for a given input program.
This allows you to assess the effectiveness of your dead code elimination optimization. You
also will be able to check for correctness of your optimization pass.
