//
// Created by Łukasz on 2018-06-06.
//.

#ifndef PROJEKT_ATTINY13_INSTRUCTION_DECODER_H
#define PROJEKT_ATTINY13_INSTRUCTION_DECODER_H

#include <fstream>
#include <iostream>

namespace project {

    class InstructionDecoder {
        class LostData {
        };

        class BadFormat {
        };

        class FileNotOpen{};
        std::ifstream hex_;
        uint16_t *program_memory_;
    public:
        uint16_t orders_quantity_;

        InstructionDecoder(const std::string path, uint16_t *memory) : program_memory_(memory), orders_quantity_(0){
            read(path);
        }

        void read(const std::string path) throw (BadFormat, LostData) {
            hex_.open(path, std::ios::in | std::ios::binary);
            if (!hex_.is_open()) throw FileNotOpen{}; // po nieotworzeniu wyjątek;

            //bufor do trzymania danych
            std::string current_line;
            //sprawdzenie otwarcia line
            while (getline(hex_, current_line)) {
                if (current_line[0] != ':') throw BadFormat(); //jezeli linia się źle zaczyna wyjątek
                //sprawdzenie sumy kontrolnej
                unsigned int check = 0;
                std::string value;
                for (unsigned int i = 0; i < (current_line.size() - 3) / 2; ++i) {
                    value = current_line.substr(i*2 + 1, 2);
                    unsigned int value_int = std::stoul(value, nullptr, 16);
                    check += value_int;
                }

                std::string control_sum_string = current_line.substr(current_line.size() - 3, 2);
                unsigned int control_sum = std::stoul(control_sum_string, nullptr, 16);
                //jezeli suma się nie zgadza oznacza to blad
                //if (control_sum != 0x100 - (check & 0xFF)) throw LostData();

                std::string number_of_bytes_string = current_line.substr(1, 2);
                unsigned int bytes_quantity = std::stoul(number_of_bytes_string, nullptr, 16);
                //kazdy opcode to 16 bajtów - 8 rozkazow
                unsigned int orders_quantity = bytes_quantity / 2;
                orders_quantity_ += orders_quantity;

                //adres do zapisu
                std::string adress_string = current_line.substr(3, 4);
                unsigned int adress_in_memory = std::stoul(adress_string, nullptr, 16) / 2;

                char type = current_line[8];
                if (type == '1') break; // 1 to koniec pliku
                else {
                    for (unsigned int i = 0; i < orders_quantity; ++i) {
                        //odczytanie rozkazów - string
                        std::string order_string = current_line.substr(9 + i * 4, 4);
                        //konwersja do liczb
                        uint16_t order = std::stoul(order_string, nullptr, 16);
                        //zapisanie do pamięci
                        program_memory_[adress_in_memory + i] = order;
                    }
                }
            }
            //zamknięcie pliku
            hex_.close();
            std::cout << "Program Loaded" << std::endl;
        }
    };
}
#endif //PROJEKT_ATTINY13_INSTRUCTION_DECODER_H
