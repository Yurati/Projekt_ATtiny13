//
// Created by Łukasz on 2018-06-08.
//

#ifndef PROJEKT_ATTINY13_DATA_TRANSFER_INTERFACE_H
#define PROJEKT_ATTINY13_DATA_TRANSFER_INTERFACE_H

namespace project {
    class DataTranserInterface {
    public:
        virtual void Mov(char &Rd, const char &Rr) = 0;

        virtual void Movw(char &Rd, const char &Rr) = 0;

        virtual void Ldi(char &Rd, const char &K) = 0;

        virtual void Ld(char &Rd) = 0;

        virtual void Ldd(char &Rd) = 0;

        virtual void Lds(char &Rd, const uint16_t &k) = 0;

        virtual void St(char &Rd) = 0;

        virtual void Std(char &Rd) = 0;

        virtual void Sts(char &Rd, const char &k) = 0;

        virtual void Lpm(char &Rd) = 0;

    };
}
#endif //PROJEKT_ATTINY13_DATA_TRANSFER_INTERFACE_H
