//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_MEMORY_H
#define PROJEKT_ATTINY13_MEMORY_H

#include "Registers.h"
#include "I_O_Registers.h"
#include "Stack.h"

namespace project {
    class Memory {
    private:
        char *memory_[0x9F];
        Registers registers_;
        I_O_Registers i_o_registers_;
        Stack stack_;
    public:
        Memory() : stack_(*memory_[0x3D]) {
            memory_[0x03] = &registers_.ADCSRB;
            memory_[0x04] = &registers_.ADCL;
            memory_[0x05] = &registers_.ADCH;
            memory_[0x06] = &registers_.ADCSRA;
            memory_[0x07] = &registers_.ADMUX;
            memory_[0x08] = &registers_.ACSR;
            memory_[0x14] = &registers_.DIDR0;
            memory_[0x15] = &registers_.PCMSK;
            memory_[0x16] = &registers_.PINB;
            memory_[0x17] = &registers_.DDRB;
            memory_[0x18] = &registers_.PORTB;
            memory_[0x1C] = &registers_.EECR;
            memory_[0x1D] = &registers_.EEDR;
            memory_[0x1E] = &registers_.EEARL;
            memory_[0x21] = &i_o_registers_.WDTCR;
            memory_[0x26] = &i_o_registers_.CLKPR;
            memory_[0x28] = &i_o_registers_.GTCCR;
            memory_[0x29] = &i_o_registers_.OCR0B;
            memory_[0x2E] = &i_o_registers_.DWDR;
            memory_[0x2F] = &i_o_registers_.TCCR0A;
            memory_[0x31] = &i_o_registers_.OSCCAL;
            memory_[0x32] = &i_o_registers_.TCNT0;
            memory_[0x33] = &i_o_registers_.TCCR0B;
            memory_[0x34] = &i_o_registers_.MCUSR;
            memory_[0x35] = &i_o_registers_.MCUCR;
            memory_[0x36] = &i_o_registers_.OCR0A;
            memory_[0x37] = &i_o_registers_.SPMCSR;
            memory_[0x38] = &i_o_registers_.TIFR0;
            memory_[0x39] = &i_o_registers_.TIMSK0;
            memory_[0x3A] = &i_o_registers_.GIFR;
            memory_[0x3B] = &i_o_registers_.GIMSK;
            memory_[0x3D] = &i_o_registers_.SPL;
            memory_[0x3F] = &i_o_registers_.SREG;
        }

        char & ReadMemory(const unsigned int adress){
            return *memory_[adress];
        }
    };

}
#endif //PROJEKT_ATTINY13_MEMORY_H
