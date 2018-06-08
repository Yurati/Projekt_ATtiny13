cmake_minimum_required(VERSION 3.9)
project(Projekt_ATtiny13)

set(CMAKE_CXX_STANDARD 11)

add_executable(Projekt_ATtiny13 main.cpp ProgramMemory.h ATtiny13.cpp ATtiny13.h Registers.h Memory.h I_O_Registers.h Stack.h ALU.cpp ALU.h ALU_Interface.h Instruction_Decoder.cpp Instruction_Decoder.h data_transfer_interface.h data_transfer.cpp data_transfer.h)