//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_INSTRUCTION_H
#define TOYJVM_INSTRUCTION_H

#include "type.h"
#include "rtda.h"
#include "bytecode.h"
#include "IS.h"

union Context {
    int index;
    int offset;
    u1 bi;
    short si;
    unsigned int atype;
};

typedef void(*Execute)(union Context *, struct Frame *);

typedef void(*FetchOperands)(union Context *, struct Bytecode *);


struct Instruction {
    FetchOperands fetchOperands;
    Execute execute;
};


struct Instruction newInstruction(u1 opcode);

#endif //TOYJVM_INSTRUCTION_H
