//
// Created by Łukasz on 2018-06-08.
//

#ifndef PROJEKT_ATTINY13_DATA_TRANSFER_H
#define PROJEKT_ATTINY13_DATA_TRANSFER_H

#include "data_transfer_interface.h"
#include "Memory.h"

namespace project {
    class DataTransfer : public DataTranserInterface {
        Registers &registers_;
        Memory &memory_;
    public:
        DataTransfer(Registers &reg, Memory &memory) : registers_(reg), memory_(memory){}

        virtual void Mov(char &Rd, const char &Rr);  //001011rdddddrrrr

        virtual void Movw(char &Rd, const char &Rr);  //00000001ddddrrrr

        virtual void Ldi(char &Rd, const char &K);  //1110KKKKddddKKKK

        virtual void Ld(char &Rd);  //1001000ddddd1100

        virtual void Ldd(char &Rd);  //1000000ddddd1000

        virtual void Lds(char &Rd, const uint16_t &k);  //1001000ddddd0000

        virtual void St(char &Rd);  //1001001rrrrr1100

        virtual void Std(char &Rd); //1000001rrrrr1000

        virtual void Sts(char &Rd, const char &k);  //1001001ddddd0000kkkkkkkkkkkkkkkkkkkk

        virtual void Lpm(char &Rd);  //1001010111001000, do R0
    };

}

#endif //PROJEKT_ATTINY13_DATA_TRANSFER_H
