//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_ATTINY13_H
#define PROJEKT_ATTINY13_ATTINY13_H

#include "Memory.h"
#include "ProgramMemory.h"
#include "ALU.h"
#include "data_transfer.h"

class ATtiny13 {
private:
    project::Memory memory_;
    project::ALU alu_;
    project::ProgramMemory program_memory_;
    project::DataTransfer data_transfer_;
public:
    ATtiny13(const std::string path): alu_(memory_), program_memory_(path, memory_.ReadMemory(0x3F)),
                                      data_transfer_(memory_.ReadRegisters(), memory_){}
    void ExecuteOrder() throw(UnknownOrder);

    void ExecuteAllOrders() throw(UnknownOrder){
        for(int i = 0; i < 403 ; ++i){
            ExecuteOrder();
        }
    }
    void DisplayFlash(){
        program_memory_.display();
    }
    void SetOpcode(uint16_t opcde){
        program_memory_.SetOpcode(opcde);
    }

    void SetRegister(const char reg, const char value){
        memory_.SetReg(reg, value);
    }
};


#endif //PROJEKT_ATTINY13_ATTINY13_H
