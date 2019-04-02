//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_ALU_H
#define PROJEKT_ATTINY13_ALU_H

#include "ALU_Interface.h"
#include "Memory.h"

namespace project {
    class ALU : public ALU_Interface {
        Memory & memory_;
        char & sreg_;
        const char kH = 5;
        const char kS = 4;
        const char kV = 3;
        const char kN = 2;
        const char kZ = 1;
        const char kC = 0;
    public:
        ALU(Memory & mem):memory_(mem), sreg_(memory_.ReadMemory(0x3F)){}
        virtual void Add(char &Rd, const char &Rr);  //000011rddddrrrr

        virtual void Adc(char &Rd, const char &Rr );  //000111rdddddrrrr

        virtual void Adiw(char &Rdl,const char &K);  //10010110KKddKKKK

        virtual void Sub(char &Rd, const char &Rr);  //000110rdddddrrrr

        virtual void Subi(char &Rd, const char &K); //0101KKKKddddKKKK

        virtual void Sbc(char &Rd, const char &Rr);  //000010rdddddrrrr

        virtual void Sbci(char &Rd, const char &K);  //0100KKKKddddKKKK

        virtual void Sbiw(char &Rdl, const char &K);  //10010111KKddKKKK

        virtual void And(char &Rd, const char &Rr);  //001000rddddrrrr

        virtual void Andi(char &Rd, const char &K);  //0111KKKKddddKKKK

        virtual void Or(char &Rd, const char &Rr);  //001010rdddddrrrr

        virtual void Ori(char &Rd, const char &K);  //0110KKKKddddKKKK

        virtual void Eor(char &Rd, const char &Rr);  //001001rdddddrrrr

        virtual void Com(char &Rd);  //1001010dddd0000

        virtual void Neg(char &Rd);  //1001010ddddd0001

        virtual void Sbr(char &Rd, const char &K);  //0110KKKKddddKKKK

        virtual void Cbr(char &Rd, const char &K);  //Andi with full K

        virtual void Inc(char &Rd);  //1001010ddddd0011

        virtual void Dec(char &Rd);  //1001010dddd1010

        virtual void Tst(char &Rd);  //001000dddddddddd;

        virtual void Clr(char &Rd);  //001001dddddddddd

        virtual void Ser(char &Rd);  //11101111dddd1111
    };
}

#endif //PROJEKT_ATTINY13_ALU_H
