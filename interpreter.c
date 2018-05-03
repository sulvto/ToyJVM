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
        u1 opcode = readBytecodeU1(bytecode_data);


        union Context *context = (union Context *) malloc(sizeof(union Context));

        struct Instruction inst = newInstruction(opcode);
        inst.fetchOperands(context, bytecode_data);
        frame->nextPC = bytecode_data->pc;

        inst.execute(context, frame);

        printf("pc:%d\n", pc);

        free(context);
    }
}

void interpret(struct Method *main_method)
{
    struct Code_attributeInfo code_attribute = main_method->attributes->code;
    const u4 code_length = code_attribute.code_length;

    struct Thread *thread = newThread();
    struct Frame *frame = newFrame(thread, main_method);
    pushFrame(frame, thread);

    loop(thread, code_attribute.code);
}
