//
// Created by Łukasz on 2018-06-05.
//

#ifndef PROJEKT_ATTINY13_ALU_INTERFACE_H
#define PROJEKT_ATTINY13_ALU_INTERFACE_H
namespace project {
    class ALU_Interface {
    public:
        // ARITHMETIC AND LOGICAL INSTRUCTIONS
        virtual void Add(char &Rd, char &Rr const) = 0;

        virtual void Adc(char &Rd, char &Rr const) = 0;

        virtual void Adiw(char &Rdl, char &K const) = 0;

        virtual void Sub(char &Rd, char &Rr const) = 0;

        virtual void Subi(char &Rd, char &K const) = 0;

        virtual void Sbc(char &Rd, char &Rr const) = 0;

        virtual void Sbci(char &Rd, char &K const) = 0;

        virtual void Sbiw(char &Rdl, char &K const) = 0;

        virtual void And(char &Rd, char &Rr const) = 0;

        virtual void Andi(char &Rd, char &K const) = 0;

        virtual void Or(char &Rd, char &Rr const) = 0;

        virtual void Ori(char &Rd, char &K const) = 0;

        virtual void Eor(char &Rd, char &Rr const) = 0;

        virtual void Com(char &Rd const) = 0;

        virtual void Neg(char &Rd) = 0;

        virtual void Sbr(char &Rd, char &K const) = 0;

        virtual void Cbr(char &Rd, char &K const) = 0;

        virtual void Inc(char &Rd)= 0;

        virtual void Dec(char &Rd) = 0;

        virtual void Tst(char &Rd) = 0;

        virtual void Clr(char &Rd) = 0;

        virtual void Ser(char &Rd) = 0;
    };
}
#endif //PROJEKT_ATTINY13_ALU_INTERFACE_H
