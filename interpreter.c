//
// Created by sulvto on 18-4-30.
//

#include "classreader.h"
#include "rtda.h"
#include "interpreter.h"
#include "bytecode.h"



void loop(struct Thread *thread, u1 *bytecode)
{
    struct Frame *frame = popFrame(thread);

    struct BytecodeData *bytecode_data = (struct BytecodeData *) malloc(sizeof(struct BytecodeReader));


    while (1) {
        int pc = frame->nextPC;
        thread->pc = pc;

        reset(bytecode, pc, bytecode_data);
        u1 opcode = readU1(bytecode_data);

        frame->nextPC = reader->pc;

//        printf("pc:%d inst:%v %v\n", pc, )

        execute(frame);
    }
}

void interpret(MemberInfo *mainMethod)
{
    struct Code_attributeInfo code_attribute = mainMethod->attributes->code;
    u2 max_locals = code_attribute.max_locals;
    u2 max_stack = code_attribute.max_stack;
    u1 bytecode[] = code_attribute.code;
    u4 code_length = code_attribute.code_length;

    struct Thread *thread = newThread();
    struct Frame *frame = newFrame(max_locals, max_stack, thread);

    loop(thread, &bytecode);
}
