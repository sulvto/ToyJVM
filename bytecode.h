//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_BYTECODE_H
#define TOYJVM_BYTECODE_H

struct BytecodeData {
    u1  *code;
    int pc;
};

void reset(u1 *code, const int pc, struct BytecodeData *data);

u1 readU1(struct BytecodeData *data);

u2 readU2(struct BytecodeData *data);


#endif //TOYJVM_BYTECODE_H
