//
// Created by sulvto on 18-4-30.
//

#include "rtda.h"
#include "bytecode.h"
#include "instruction.h"

void nop_fetchOp(union Context *context, struct BytecodeData *data)
{
    // noting to do
}

void branch_fetchOp(union Context *context, struct BytecodeData *data)
{
    context->offset = readU2(data);
}

void index8_fetchOp(union Context *context, struct BytecodeData *data)
{
    context->index = readU1(data);
}

void index16_fetchOp(union Context *context, struct BytecodeData *data)
{
    context.index = readU2(data);
}


void nop_execute(union Context *context, struct Frame *frame)
{

}


void ACONST_NULL_execute(struct Frame *frame)
{
    pushRef(NULL, frame->operand_stack);
}

void DCONST_0_execute(struct Frame *frame)
{
    pushDouble(0.0, frame->operand_stack);
}

void branch(struct Frame *frame, int offset)
{
    int pc = frame->thread->pc;
    frame->nextPC = pc + offset;
}

struct Instruction *newInstruction(u1 opcode)
{
    switch (opcode) {
        case NOP:
            // TODO
        case :
    }
}