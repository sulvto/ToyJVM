//
// Created by sulvto on 18-4-30.
//

#include "type.h"
#include "bytecode.h"
#include "classreader.h"
#include "rtda.h"
#include "interpreter.h"
#include "instruction.h"


void loop(struct Thread *thread, u1 *bytecode)
{
    struct Frame *frame = popFrame(thread);

    struct Bytecode *bytecode_data = (struct Bytecode *) malloc(sizeof(struct Bytecode));


    while (1) {
        int pc = frame->nextPC;
        thread->pc = pc;

        reset(bytecode, pc, bytecode_data);
        u1 opcode = readU1(bytecode_data);

        union Context *context = (union Context *) malloc(sizeof(union Context));

        struct Instruction inst = newInstruction(opcode);
        inst.fetchOperands(context, bytecode_data);
        frame->nextPC = bytecode_data->pc;

        inst.execute(context, frame);

        free(context);
    }
}

void interpret(struct MemberInfo *mainMethod)
{
    struct Code_attributeInfo code_attribute = mainMethod->attributes->code;
    u2 max_locals = code_attribute.max_locals;
    u2 max_stack = code_attribute.max_stack;
    const u4 code_length = code_attribute.code_length;
    u1 *bytecode = (u1*)malloc(sizeof(u1) * code_length);
    *bytecode = code_attribute.code;

    struct Thread *thread = newThread();
    struct Frame *frame = newFrame(max_locals, max_stack, thread);

    loop(thread, bytecode);
}
