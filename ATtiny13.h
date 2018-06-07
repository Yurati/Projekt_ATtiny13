//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_ATTINY13_H
#define PROJEKT_ATTINY13_ATTINY13_H

#include <stdint-gcc.h>
#include "Memory.h"
#include "ProgramMemory.h"
#include "ALU.h"
#include "Instruction_Decoder.h"

class ATtiny13 {
private:
    project::ALU alu_;
    project::ProgramMemory program_memory_;
    project::Memory memory_;
    project::Instruction_Decoder instruction_decoder_;
    uint16_t program_counter_;
public:
    ATtiny13(): alu_(memory_.ReadMemory(0x1F)){} //przekazanie do ALU SREG
};


#endif //PROJEKT_ATTINY13_ATTINY13_H
