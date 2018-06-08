//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_STACK_H
#define PROJEKT_ATTINY13_STACK_H

#include <stack>

namespace project {
    class Stack {
        class NoSpace{};
        std::stack<char> stack_;
        char & spl_;
    public:
        Stack(char & spl): spl_(spl){
            spl_ = 0x9F;
        };

        void Push(const char data){
            stack_.push(data);
            spl_ -= 1;
            if (spl_ < 0x60) throw NoSpace();
        }

        char Pop(){
            char top_of_stack = stack_.top();
            stack_.pop();
            spl_ += 1;
            return top_of_stack;
        }
    };
}
#endif //PROJEKT_ATTINY13_STACK_H
