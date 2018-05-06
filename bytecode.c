//
// Created by sulvto on 18-4-30.
//

#include "type.h"
#include "bytecode.h"

void reset(u1 *code, const int pc, struct Bytecode *data) {
    data->code = code;
    data->pc = pc;
}

u1 readBytecodeU1(struct Bytecode *data) {
    return data->code[data->pc++];
}

u2 readBytecodeU2(struct Bytecode *data) {
    u2 d = readBytecodeU1(data);
    return d << 8 | readBytecodeU1(data);
}
