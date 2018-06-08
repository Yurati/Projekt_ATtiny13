//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_ALU_H
#define PROJEKT_ATTINY13_ALU_H

#include "ALU_Interface.h"


namespace project {
    class ALU : public ALU_Interface {
        char & sreg_;
        const char kH = 5;
        const char kS = 4;
        const char kV = 3;
        const char kN = 2;
        const char kZ = 1;
        const char kC = 0;
    public:
        ALU(char & sreg): sreg_(sreg){}
        virtual void Add(char &Rd, const char &Rr);

        virtual void Adc(char &Rd, const char &Rr );

        virtual void Adiw(char &Rdl,const char &K);

        virtual void Sub(char &Rd, const char &Rr);

        virtual void Subi(char &Rd, const char &K);

        virtual void Sbc(char &Rd, const char &Rr);

        virtual void Sbci(char &Rd, const char &K);

        virtual void Sbiw(char &Rdl, const char &K);

        virtual void And(char &Rd, const char &Rr);

        virtual void Andi(char &Rd, const char &K);

        virtual void Or(char &Rd, const char &Rr);

        virtual void Ori(char &Rd, const char &K);

        virtual void Eor(char &Rd, const char &Rr);

        virtual void Com(char &Rd);

        virtual void Neg(char &Rd);

        virtual void Sbr(char &Rd, const char &K);

        virtual void Cbr(char &Rd, const char &K);

        virtual void Inc(char &Rd);

        virtual void Dec(char &Rd);

        virtual void Tst(char &Rd);

        virtual void Clr(char &Rd);

        virtual void Ser(char &Rd);
    };
}

#endif //PROJEKT_ATTINY13_ALU_H
