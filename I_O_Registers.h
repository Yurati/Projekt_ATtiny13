//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_I_O_REGISTERS_H
#define PROJEKT_ATTINY13_I_O_REGISTERS_H
namespace project{
    class I_O_Registers{
    public:
        char WDTCR;  //0x21
        char CLKPR;  //0x26
        char GTCCR;  //0x28
        char OCR0B;  //0x29
        char DWDR;   //0x2E
        char TCCR0A; //0x2F
        char OSCCAL; //0x31
        char TCNT0;  //0x32
        char TCCR0B; //0x33
        char MCUSR;  //0x34
        char MCUCR;  //0x35
        char OCR0A;  //0x36
        char SPMCSR; //0x37
        char TIFR0;  //0x38
        char TIMSK0; //0x39
        char GIFR;   //0x3A
        char GIMSK;  //0x3B
        char SPL;    //0x3D STACK POINTER
        char SREG;   //0x3F STATUS REGISTER
        I_O_Registers(){
            WDTCR, CLKPR, GTCCR, OCR0B, DWDR, TCCR0A, OSCCAL, TCNT0,
            TCCR0B, MCUSR, MCUCR, OCR0A, SPMCSR, TIFR0, TIMSK0, GIFR,
            GIMSK, SPL, SREG = 0;
        }
    };
}
#endif //PROJEKT_ATTINY13_I_O_REGISTERS_H
