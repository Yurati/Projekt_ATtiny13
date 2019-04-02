//
// Created by Łukasz on 2018-06-03.
//

#include "ATtiny13.h"
void ATtiny13::ExecuteOrder() throw(UnknownOrder) {
    uint16_t opcode = program_memory_.ReadOrder();//odczytanie rozkazu
    std::cout << std::hex << opcode << std::dec << std::endl;
    if (opcode == 0) {
        std::cout << "NOP " << std::endl;
        program_memory_.Nop();
    }
    else if ((opcode & 0xFF00) == 0x0100) {
        char Rd = (opcode & 0x00F0) / 8;
        char Rr = (opcode & 0x000F) * 2;
        std::cout << "MOVW " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        data_transfer_.Movw(memory_.ReadMemory(Rd),
                            memory_.ReadMemory(Rr));
    } else if ((opcode & 0xFC00) == 0x2000) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        if(Rr == Rd) {
            std::cout << "TST " << static_cast<unsigned>(Rd) << std::endl;
            alu_.Tst(memory_.ReadMemory(Rd));
        }
        else{
            std::cout << "AND " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
            alu_.And(memory_.ReadMemory(Rd), memory_.ReadMemory(Rr));
        }
    } else if ((opcode & 0xFC00) == 0x0800) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "SBC " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Sbc(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFC00) == 0x1800) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "SUB " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Sub(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFC00) == 0x0C00) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "ADD " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Add(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFC00) == 0x1C00) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "ADC " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Adc(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    }else if ((opcode & 0xFC00) == 0x2800) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "OR " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Or(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFC00) == 0x2400) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "EOR " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        alu_.Eor(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFC00) == 0x2C00) {
        char Rd = (opcode & 0x00F0) / 16;
        char Rr = opcode & 0x00F;
        if(opcode & 0x0200) Rr += 16;
        if(opcode & 0x0100) Rd += 16;
        std::cout << "MOV " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Rr) << std::endl;
        data_transfer_.Mov(memory_.ReadMemory(Rr), memory_.ReadMemory(Rd));
    } else if ((opcode & 0xF000) == 0x4000) {
        char Rd = (opcode & 0x00F0) / 16 + 16;
        char K_low = opcode & 0x000F;
        unsigned char K_Up = (opcode & 0x0F00) / 16;
        unsigned char K = K_low + K_Up;
        std::cout << "SBCI " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Sbci(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xF000) == 0x5000) {
        char Rd = (opcode & 0x00F0) / 16 + 16;
        char K_low = opcode & 0x000F;
        unsigned char K_Up = (opcode & 0x0F00) / 16;
        unsigned char K = K_low + K_Up;
        std::cout << "SUBI " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Subi(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xF000) == 0x6000) {
        char Rd = (opcode & 0x00F0) / 16 + 16;
        char K_low = opcode & 0x000F;
        unsigned char K_Up = (opcode & 0x0F00) / 16;
        unsigned char K = K_low + K_Up;
        std::cout << "ORI " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Ori(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xF000) == 0x7000) {
        char Rd = (opcode & 0x00F0) / 16 + 16;
        char K_low = opcode & 0x000F;
        unsigned char K_Up = (opcode & 0x0F00) / 16;
        unsigned char K = K_low + K_Up;
        std::cout << "ANDI " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Andi(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xD208) == 0x8000) {
        char Rd = (opcode & 0x01F0) / 16;
        char Q = (opcode & 0x0007) + (opcode & 0x0C00) / 64 + (opcode & 0x2000) / 128;
        std::cout << "LDD " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Q) << std::endl;
        data_transfer_.Ldd(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xD208) == 0x8208) {
        char Rd = (opcode & 0x01F0) / 16;
        char Q = (opcode & 0x0007) + (opcode & 0x0C00) / 64 + (opcode & 0x2000) / 128;
        std::cout << "STD " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(Q) << std::endl;
        data_transfer_.Std(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x900C) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "LD " << static_cast<unsigned>(Rd) <<std::endl;
        data_transfer_.Ld(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x900F) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "POP " << static_cast<unsigned>(Rd) <<std::endl;
        memory_.stack_.Pop(Rd);
    } else if ((opcode & 0xFE0F) == 0x920F) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "PUSH " << static_cast<unsigned>(Rd) <<std::endl;
        memory_.stack_.Push(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x920C) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "ST " << static_cast<unsigned>(Rd) << std::endl;
        data_transfer_.St(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x9401) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "NEG " << static_cast<unsigned>(Rd) << std::endl;
        alu_.Neg(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x9403) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "INC " << static_cast<unsigned>(Rd) << std::endl;
        alu_.Inc(memory_.ReadMemory(Rd));
    } else if ((opcode & 0xFE0F) == 0x940A) {
        char Rd = (opcode & 0x01F0) / 16;
        std::cout << "DEC " << static_cast<unsigned>(Rd) << std::endl;
        alu_.Dec(memory_.ReadMemory(Rd));
    } else if (opcode == 0x96C8) {
        std::cout << "LPM "<< std::endl;
        data_transfer_.Lpm(memory_.ReadMemory(0x1F));
    } else if ((opcode & 0xFF00) == 0x9600) {
        char Rd = (opcode & 0x0030) / 16;
        if (Rd == 0) Rd = 24;
        else if(Rd == 1) Rd = 26;
        else if (Rd == 2) Rd = 28;
        else if (Rd == 3) Rd = 30;
        char K_up = (opcode & 0x00C0) / 4;
        char K_down = opcode & 0x000F;
        char K = K_up + K_down;
        std::cout << "Adiw " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Adiw(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xFF00) == 0x9700) {
        char Rd = (opcode & 0x0030) / 16;
        if (Rd == 0) Rd = 24;
        else if (Rd == 1) Rd = 26;
        else if (Rd == 2) Rd = 28;
        else if (Rd == 3) Rd = 30;
        char K_up = (opcode & 0x00C0) / 4;
        char K_down = opcode & 0x000F;
        char K = K_up + K_down;
        std::cout << "Sbiw " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        alu_.Sbiw(memory_.ReadMemory(Rd), K);
    }else if ((opcode & 0xFE00) == 0xA000) {
        char Rd = (opcode & 0x01F0);
        char K_low = opcode & 0x000F;
        unsigned int K_Up = (opcode & 0x0700) / 16;
        unsigned int K = K_low + K_Up;
        std::cout << "LDS " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        data_transfer_.Lds(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xF000) == 0xC000) {
        int K = opcode & 0x0FFF;
        std::cout << "RJMP " << K << std::endl;
        program_memory_.RJMP(K);
    } else if ((opcode & 0xFE0E) == 0x940C){
        unsigned int K = (opcode & 0x01F0) * 256 + (opcode & 0x0001) * 128;
        program_memory_.next();
        opcode = program_memory_.ReadOrder();
        K += opcode;
        std::cout << "Order JMP "<< K << std::endl;
        program_memory_.JMP(K);
    } else if ((opcode & 0xF000) == 0xE000) {
        char Rd = (opcode & 0x00F0) / 16 + 16;
        char K_low = opcode & 0x000F;
        unsigned int K_Up = (opcode & 0x0F00) / 16;
        unsigned int K = K_low + K_Up;
        std::cout << "LDI " << static_cast<unsigned>(Rd) << "," << static_cast<unsigned>(K) << std::endl;
        data_transfer_.Ldi(memory_.ReadMemory(Rd), K);
    } else if ((opcode & 0xFC07) == 0xF000){
        char K = (opcode & 0x03F8) / 8;
        std::cout << "BRCS " << static_cast<int>(K) << std::endl;
        program_memory_.BRCS(K);
    } else if ((opcode & 0xFE08) == 0xFC00) {
        char Rr = (opcode & 0x01F0) / 16;
        char b = opcode & 0x0007;
        std::cout << "SBRC " << static_cast<unsigned>(Rr) << "," << static_cast<unsigned>(b) << std::endl;
        program_memory_.SBRC(memory_.ReadMemory(Rr), b);
    } else if ((opcode & 0xFE08) == 0xFE00) {
        char Rr = (opcode & 0x01F0) / 16;
        char b = opcode & 0x0007;
        std::cout << "SBRS " << static_cast<unsigned>(Rr) << "," << static_cast<unsigned>(b) << std::endl;
        program_memory_.SBRS(memory_.ReadMemory(Rr), b);
    }
    else std::cout << "Uknown order" << std::endl;
    program_memory_.next();
}