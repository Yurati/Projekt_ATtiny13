//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_ALU_H
#define PROJEKT_ATTINY13_ALU_H

#include "ALU_Interface.h"

const char kH = 5;
const char kS = 4;
const char kV = 3;
const char kN = 2;
const char kZ = 1;
const char kC = 0;

namespace project {
    class ALU : public ALU_Interface {
        char & sreg_;
    public:
        ALU(char & sreg): sreg_(sreg){}
        virtual void Add(char &Rd, char &Rr const){
            char R = Rd + Rr;
            bool H = ((Rd & (1<<3)) & (Rr & (1<<3))) + ((Rr & (1<<3)) & ~(R & (1<<3))) + (~(R & (1<<3)) & (Rd & (1<<3)));
            bool V = (Rd & (1<<7)) & (Rr & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) + ~(Rr & (1<<7)) & (R & (1<<7));
            bool N = R & (1<<7);
            bool S = V ^ N;
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                    ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = (Rd & (1<<7)) & (Rr & (1<<7)) + (Rr & (1<<7)) & ~(R & (1<<7)) + ~(R & (1<<7)) & (Rd & (1<<7));
            Rd = R;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ |= sreg_copy;
        };

        virtual void Adc(char &Rd, char &Rr const){
            char R = Rd + Rr;
            bool H = ((Rd & (1<<3)) & (Rr & (1<<3))) + ((Rr & (1<<3)) & ~(R & (1<<3))) + (~(R & (1<<3)) & (Rd & (1<<3)));
            bool V = (Rd & (1<<7)) & (Rr & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) + ~(Rr & (1<<7)) & (R & (1<<7));
            bool N = R & (1<<7);
            bool S = V ^ N;
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                    ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = (Rd & (1<<7)) & (Rr & (1<<7)) + (Rr & (1<<7)) & ~(R & (1<<7)) + ~(R & (1<<7)) & (Rd & (1<<7));
            Rd = R + C;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ | sreg_copy;
        };

        virtual void Adiw(char &Rdl, char &K const);

        virtual void Sub(char &Rd, char &Rr const){
            char R = Rd - Rr;

            bool H = ~(Rd & (1<<3)) & (Rr & (1<<3)) + (Rr & (1<<3)) & (R & (1<<3))  + (R & (1<<3)) & ~(Rd & (1<<3));
            bool V = (Rd & (1<<7)) & ~(Rr & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) & (Rr & (1<<7)) & (R & (1<<7));
            bool N = (R & (1<<7));
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = ~(Rd & (1<<7)) & (Rr & (1<<7)) + (Rr & (1<<7)) & (R & (1<<7)) + (R & (1<<7)) & (Rd & (1<<7));
            bool S = N ^ V;

            Rd = R;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ | sreg_copy;
        };

        virtual void Subi(char &Rd, char &K const){
            char R = Rd - K;

            bool H = ~(Rd & (1<<3)) & (K & (1<<3)) + (K & (1<<3)) & (R & (1<<3))  + (R & (1<<3)) & ~(Rd & (1<<3));
            bool V = (Rd & (1<<7)) & ~(K & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) & (K & (1<<7)) & (R & (1<<7));
            bool N = (R & (1<<7));
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = ~(Rd & (1<<7)) & (K & (1<<7)) + (K & (1<<7)) & (R & (1<<7)) + (R & (1<<7)) & (Rd & (1<<7));
            bool S = N ^ V;

            Rd = R;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ | sreg_copy;
        };

        virtual void Sbc(char &Rd, char &Rr const){
            char R = Rd - Rr;

            bool H = ~(Rd & (1<<3)) & (Rr & (1<<3)) + (Rr & (1<<3)) & (R & (1<<3))  + (R & (1<<3)) & ~(Rd & (1<<3));
            bool V = (Rd & (1<<7)) & ~(Rr & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) & (Rr & (1<<7)) & (R & (1<<7));
            bool N = (R & (1<<7));
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = ~(Rd & (1<<7)) & (Rr & (1<<7)) + (Rr & (1<<7)) & (R & (1<<7)) + (R & (1<<7)) & (Rd & (1<<7));
            bool S = N ^ V;

            Rd = R - C;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ | sreg_copy;
        };

        virtual void Sbci(char &Rd, char &K const){
            char R = Rd - K;

            bool H = ~(Rd & (1<<3)) & (K & (1<<3)) + (K & (1<<3)) & (R & (1<<3))  + (R & (1<<3)) & ~(Rd & (1<<3));
            bool V = (Rd & (1<<7)) & ~(K & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) & (K & (1<<7)) & (R & (1<<7));
            bool N = (R & (1<<7));
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool C = ~(Rd & (1<<7)) & (K & (1<<7)) + (K & (1<<7)) & (R & (1<<7)) + (R & (1<<7)) & (Rd & (1<<7));
            bool S = N ^ V;

            Rd = R - C;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ | sreg_copy;
        };

        virtual void Sbiw(char &Rdl, char &K const);

        virtual void And(char &Rd, char &Rr const){
            char R = Rd & Rr;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                    ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Andi(char &Rd, char &K const){
            char R = Rd & K;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Or(char &Rd, char &Rr const){
            char R = Rd | Rr;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Ori(char &Rd, char &K const){
            char R = Rd | K;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Eor(char &Rd, char &Rr const){
            char R = Rd ^ Rr;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Com(char &Rd){
            char R = 0xFF - Rd;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ) | (1 << kC);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Neg(char &Rd){
            char R = 0 - Rd;

            bool H = (R & (1<<3)) + (Rd & (1<<3));
            bool N = R & (1<<7);
            bool V = (R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            bool C = (R & (1<<7)) + (R & (1<<6)) + (R & (1<<5)) + (R & (1<<4)) + (R & (1<<3)) + (R & (1<<2))+
                     (R & (1<<1)) + (R & (1<<0));
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Sbr(char &Rd, char &K const){
            char R = Rd | R;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Cbr(char &Rd, char &K const){
            char R = Rd & (0xFF - K);
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Inc(char &Rd){
            char R = Rd + 1;

            bool V = (R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) + ~(Rd & (1<<4)) + ~(R & (1<<3)) & ~(R & (1<<2)) &
                    ~(R & (1<<1)) & ~(R & (1<<0));
            bool N = R & (1<<7);
            bool S = N ^ V;
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));

            Rd = R;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (V << kV) | (N << kN) | (Z << kZ);
            sreg_ | sreg_copy;
        };

        virtual void Dec(char &Rd){
            char R = Rd - 1;

            bool V = ~(R & (1<<7)) & (R & (1<<6)) & (R & (1<<5)) + (Rd & (1<<4)) + (R & (1<<3)) & (R & (1<<2)) &
                    (R & (1<<1)) & (R & (1<<0));
            bool N = R & (1<<7);
            bool S = N ^ V;
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));

            Rd = R;
            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (V << kV) | (N << kN) | (Z << kZ);
            sreg_ | sreg_copy;
        };

        virtual void Tst(char &Rd){
            char R = Rd & Rd;
            bool V = 0;
            bool N = R & (1<<7);
            bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
                     ~(R & (1<<1)) & ~(R & (1<<0));
            bool S = N ^ V;
            char bit_mask = 255 & ~(1<<kV);

            char sreg_copy = sreg_;
            sreg_ = 0;
            sreg_ |= (S << kS) | (N << kN) | (Z << kZ);
            sreg_ &= bit_mask;
            sreg_ |= sreg_copy;
            Rd = R;
        };

        virtual void Clr(char &Rd){
            Rd ^= Rd;
            sreg_ &= ~(1<<kS) & ~(1<<kV) & ~(1<<kN);
            sreg_ |= (1<<kZ);
        };

        virtual void Ser(char &Rd){
            Rd = 0xFF;
        };
    };
}

#endif //PROJEKT_ATTINY13_ALU_H
