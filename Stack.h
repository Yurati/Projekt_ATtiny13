//
// Created by Łukasz on 2018-06-03.
//

#ifndef PROJEKT_ATTINY13_STACK_H
#define PROJEKT_ATTINY13_STACK_H

#include <stack>
#include <iostream>

namespace project {
    class Stack {
        class NoSpace{};
        class EmptyStack{};
        std::stack<char> stack_;
    public:
        char & spl_;
        Stack(char & spl): spl_(spl){
            spl_ = 0x9F - 0x60;
        };
        void Push(const char data){
            stack_.push(data);
            spl_ -= 1;
            if (spl_ < 0) throw NoSpace();
        }  //1001001ddddd1111

        char Pop(char Rd){
            if (stack_.empty()) throw EmptyStack{};
            char top_of_stack = stack_.top();
            stack_.pop();
            spl_ += 1;
            return top_of_stack;
        }  //1001000ddddd1111
    };
}
#endif //PROJEKT_ATTINY13_STACK_H
