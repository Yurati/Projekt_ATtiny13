//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_REGISTERS_H
#define PROJEKT_ATTINY13_REGISTERS_H

#include <cstdint>

namespace project{
    class Registers{
    public:
        char ADCSRB; //0x03
        char ADCL;   //0x04
        char ADCH;   //0x05
        char ADCSRA; //0x06
        char ADMUX;  //0x07
        char ACSR;   //0x08
        char DIDR0;  //0x014
        char PCMSK;  //0x015
        char PINB;   //0x016
        char DDRB;   //0x017
        char PORTB;  //0x018
        //Z
        char XLOW;   //0x1A
        char XHIGH;  //0x1B
        //Y
        char EECR;   //0x01C
        char EEDR;   //0x1D
        //Z
        char EEARL;  //0x1E
        char ZHIGH;  //0x1F

        Registers(){
            ADCSRB, ADCL, ADCH, ADCSRA, ADMUX, ACSR, DIDR0, PCMSK,
                    PINB, DDRB, PORTB, XLOW, XHIGH, EECR, EEDR, EEARL,
                    ZHIGH = 0;
        }


    };
}
#endif //PROJEKT_ATTINY13_REGISTERS_H
