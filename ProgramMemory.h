//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_PROGRAMMEMORY_H
#define PROJEKT_ATTINY13_PROGRAMMEMORY_H


#include <cstdint>
#include "Instruction_Decoder.h"

class UnknownOrder{};

namespace project {
    class ProgramMemory {
    private:
        uint16_t program_memory_[512];
        uint16_t program_counter_;
        InstructionDecoder instruction_decoder_;
        //operacje na pamięci programu
        char &sreg_;
    public:
        ProgramMemory(const std::string path, char & sreg) : program_counter_(0), instruction_decoder_(path, program_memory_), sreg_(sreg){}
        void next(){
            ++program_counter_;
        }
        //skoki
        void RJMP(const int k){
           program_counter_ += k + 1;
        }; //1100kkkkkkkkkkkk
        void JMP(const unsigned int k) {
            program_counter_ = k;
        }; //1001010kkkkk110k
        void SBRC(const char &Rd, const char b){ //1111110rrrrr0bbb
            char result = Rd & (1<<b);
            if (result == 0){
                program_counter_ += 2;
            }
            else next();
        };
        void SBRS(const char &Rd, const char b){
            char result = Rd & (1<<b);
            if (result == 1){
                program_counter_ +=2;
            }
            else next();
        }; //1111111rrrr0bbb
        void BRCS(const int8_t K){
            std::cout << "Carry " << (sreg_ & 0x01) << std::endl;
            if(!(sreg_ & 0x01)) program_counter_ = program_counter_ - K;
            else next();
        }

        //operacja nic nie robiąca
        void Nop(){}   //0000000000000000

        //wyswietlanie flash
        void display(){
            for(int i = 0; i < instruction_decoder_.orders_quantity_ - 1; ++i){
                std::cout << std::hex << program_memory_[i] << std::endl;
            }
        }
        uint16_t ReadOrder(){
            return program_memory_[program_counter_];
        }
        void SetOpcode(uint16_t code){
            program_memory_[0] = code;
            program_counter_ = 0;
        }
        uint16_t Quantity(){
            return instruction_decoder_.orders_quantity_;
        }
        ~ProgramMemory(){}
    };
}
#endif //PROJEKT_ATTINY13_PROGRAMMEMORY_H
