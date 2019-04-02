//
// Created by Łukasz on 2018-06-03.
//

#include "ALU.h"
#include <iostream>

void project::ALU::Add(char &Rd, const char &Rr){
    char R = Rd + Rr;
    std::cout << static_cast<int>(Rd) << std::endl;
    std::cout << static_cast<int>(Rr) << std::endl;
    std::cout << static_cast<int>(R) << std::endl;
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

void project::ALU::Adc(char &Rd, const char &Rr ){
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

void project::ALU::Adiw(char &Rdl,const char &K){
    char &Rd2 = memory_.ReadMemory(Rdl + 1);
    if (Rdl + K > 255){
        Rdl -= 255;
        Rd2 += 1;
    }
    Rdl += K;

    bool V = ~(Rdl & (1<<7)) & (Rd2 & (1<<7));
    bool N = Rd2 & (1<<7);
    bool S = N ^ V;
    bool Z;
    if (Rd2 == 0 and Rdl == 0) Z = 1;
    else Z = 0;
    bool C = ~(Rd2 & (1<<7)) & (Rdl & (1<<7));

    char sreg_copy = sreg_;
    sreg_ = 0;
    sreg_ |= (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
    sreg_ |= sreg_copy;

};

void project::ALU::Sub(char &Rd, const char &Rr){
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
    sreg_ |= sreg_copy;
};

void project::ALU::Subi(char &Rd, const char &K){
    unsigned char R = Rd - K;
    std::cout << static_cast<unsigned >(R) << std::endl;
    bool H = ~(Rd & (1<<3)) & (K & (1<<3)) + (K & (1<<3)) & (R & (1<<3))  + (R & (1<<3)) & ~(Rd & (1<<3));
    bool V = (Rd & (1<<7)) & ~(K & (1<<7)) & ~(R & (1<<7)) + ~(Rd & (1<<7)) & (K & (1<<7)) & (R & (1<<7));
    bool N = (R & (1<<7));
    bool Z = ~(R & (1<<7)) & ~(R & (1<<6)) & ~(R & (1<<5)) & ~(R & (1<<4)) & ~(R & (1<<3)) & ~(R & (1<<2))&
             ~(R & (1<<1)) & ~(R & (1<<0));
    bool C = ~(Rd & (1<<7)) & (K & (1<<7)) + (K & (1<<7)) & (Rd & (1<<7)) + (R & (1<<7)) & ~(Rd & (1<<7));
    if (R == 255) std::cout << C << std::endl;
    bool S = N ^ V;

    Rd = R;
    char sreg_copy = sreg_;
    sreg_ = 0;
    sreg_ |= (H << kH) | (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
    sreg_ |= sreg_copy;
};

void project::ALU::Sbc(char &Rd, const char &Rr){
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
    sreg_ |= sreg_copy;
};

void project::ALU::Sbci(char &Rd, const char &K){
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
    sreg_ |= sreg_copy;
};

void project::ALU::Sbiw(char &Rdl, const char &K){
    char &Rd2 = memory_.ReadMemory(Rdl + 1);
    if (Rdl - K < 255){
        Rdl += 255;
        Rd2 -= 1;
    }
    Rdl -= K;

    bool V = (Rdl & (1<<7)) & ~(Rd2 & (1<<7));
    bool N = Rd2 & (1<<7);
    bool S = N ^ V;
    bool Z;
    if (Rd2 == 0 and Rdl == 0) Z = 1;
    else Z = 0;
    bool C = (Rd2 & (1<<7)) & ~(Rdl & (1<<7));

    char sreg_copy = sreg_;
    sreg_ = 0;
    sreg_ |= (S << kS) | (V << kV) | (N << kN) | (Z << kZ) | (C << kC);
    sreg_ |= sreg_copy;
};

void project::ALU::And(char &Rd, const char &Rr){
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

void project::ALU::Andi(char &Rd, const char &K){
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

void project::ALU::Or(char &Rd, const char &Rr){
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

void project::ALU::Ori(char &Rd, const char &K){
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

void project::ALU::Eor(char &Rd, const char &Rr){
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

void project::ALU::Com(char &Rd){
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

void project::ALU::Neg(char &Rd){
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

void project::ALU::Sbr(char &Rd, const char &K){
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

void project::ALU::Cbr(char &Rd, const char &K){
    std::cout << "Order CBR " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
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

void project::ALU::Inc(char &Rd){
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

void project::ALU::Dec(char &Rd){
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

void project::ALU::Tst(char &Rd){
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

void project::ALU::Clr(char &Rd){
    Rd ^= Rd;
    sreg_ &= ~(1<<kS) & ~(1<<kV) & ~(1<<kN);
    sreg_ |= (1<<kZ);
};

void project::ALU::Ser(char &Rd){
    Rd = 0xFF;
};