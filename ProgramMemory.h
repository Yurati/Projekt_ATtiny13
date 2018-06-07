//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_PROGRAMMEMORY_H
#define PROJEKT_ATTINY13_PROGRAMMEMORY_H

namespace project {
    class ProgramMemory {
    private:
        char *program_memory_;
    public:
        ProgramMemory() {
            program_memory_ = new char[1024];
        }
    };
}
#endif //PROJEKT_ATTINY13_PROGRAMMEMORY_H
