//
// Created by Łukasz on 2018-06-08.
//

#ifndef PROJEKT_ATTINY13_DATA_TRANSFER_H
#define PROJEKT_ATTINY13_DATA_TRANSFER_H

#include "data_transfer_interface.h"

namespace project {
    class DataTransfer : public DataTranserInterface {
    public:
        virtual void Mov(char &Rd, const char &Rr);

        virtual void Movw(char &Rd, const char &Rr);

        virtual void Ldi(char &Rd, const char &K);

        virtual void Ld(char &Rd, const char &X);

        virtual void Ldd(char &Rd, const char &Y, const char &q);

        virtual void Lds(char &Rd, const char &k);

        virtual void St(char &Rd, const char &k);

        virtual void Std(char &Rd, const char &Y, const char &q);

        virtual void Sts(char &Rd, const char &k);

        virtual void Lpm(char &Rd, const char &Y, const char &q);
    };

}

#endif //PROJEKT_ATTINY13_DATA_TRANSFER_H
