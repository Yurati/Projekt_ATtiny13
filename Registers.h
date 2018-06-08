//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_REGISTERS_H
#define PROJEKT_ATTINY13_REGISTERS_H
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
        char EECR;   //0x01C
        char EEDR;   //0x1D
        char EEARL;  //0x1E

        Registers(){
            ADCSRB, ADCL, ADCH, ADCSRA, ADMUX, ACSR, DIDR0, PCMSK
                    ,PINB, DDRB, PORTB, EECR, EEDR, EEARL = 0;
        }


    };
}
#endif //PROJEKT_ATTINY13_REGISTERS_H
