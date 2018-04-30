//
// Created by sulvto on 18-4-30.
//

#include "type.h"
#include "bytecode.h"

void reset(u1 *code, const int pc, struct BytecodeData *data)
{
    data->code = code;
    data->pc = pc;
}

u1 readU1(struct BytecodeData *data)
{
    return data->code[data->pc++];
}

u2 readU2(struct BytecodeData *data)
{
    u2 d = readU1(reader);
    return d << 8 | readU1(reader);
}
