//
// Created by Łukasz on 2018-06-08.
//

#include <cstdint>
#include "data_transfer.h"

void project::DataTransfer::Mov(char &Rd, const char &Rr){
    Rd = Rr;
}

void project::DataTransfer::Movw(char &Rd, const char &Rr){
    Rd = Rr;
}

void project::DataTransfer::Ldi(char &Rd, const char &K){
    Rd = K;
}

void project::DataTransfer::Ld(char &Rd){
    uint16_t X = registers_.XLOW | registers_.XHIGH * 256;
    Rd = X;
}

void project::DataTransfer::Ldd(char &Rd){
    uint16_t Y = registers_.XLOW | registers_.XHIGH * 256;
    Rd = Y;
}

void project::DataTransfer::Lds(char &Rd, const uint16_t &k){
    Rd = k;
}

void project::DataTransfer::St(char &Rd){
    registers_.XLOW = Rd;
    registers_.XHIGH = 0;
}

void project::DataTransfer::Std(char &Rd){
    registers_.EECR = Rd;
    registers_.EEDR = 0;
}

void project::DataTransfer::Sts(char &Rd, const char &k){
    memory_.ReadMemory(k) = Rd;
}

void project::DataTransfer::Lpm(char &Rd){
    uint16_t Z = registers_.ZHIGH * 256 | registers_.EEARL;
    Rd = Z;
}