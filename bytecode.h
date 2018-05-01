//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_BYTECODE_H
#define TOYJVM_BYTECODE_H

#include "type.h"

struct Bytecode {
    u1  *code;
    int pc;
};

void reset(u1 *code, const int pc, struct Bytecode *data);

u1 readBytecodeU1(struct Bytecode *data);

u2 readBytecodeU2(struct Bytecode *data);


#endif //TOYJVM_BYTECODE_H
