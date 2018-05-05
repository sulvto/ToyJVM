//
// Created by sulvto on 18-4-30.
//

#include "type.h"
#include "bytecode.h"
#include "classreader.h"
#include "rtda.h"
#include "interpreter.h"
#include "instruction.h"
#include <stddef.h>

void invokeMethod(struct Frame *invoker_frame, struct Method *method)
{
    struct Thread *thread = invoker_frame->thread;
    struct Frame *new_frame = newFrame(thread, method);
    pushFrame(new_frame, thread);
    if (method->arg_count > 0) {
        for (int i = method->arg_count - 1; i >= 0; --i) {
            struct Slot slot = popSlot(invoker_frame->operand_stack);
            setSlot(i, slot, new_frame->localVars);
        }
    }
}



void loop(struct Thread *thread)
{

    struct Bytecode *bytecode_data = (struct Bytecode *) malloc(sizeof(struct Bytecode));


    while (1) {
        // current frame
        struct Frame *frame = topFrame(thread);

        int pc = frame->nextPC;
        thread->pc = pc;

        reset(frame->method->code, pc, bytecode_data);
        u1 opcode = readBytecodeU1(bytecode_data);


        union Context *context = (union Context *) malloc(sizeof(union Context));

        struct Instruction inst = newInstruction(opcode);
        inst.fetchOperands(context, bytecode_data);
        frame->nextPC = bytecode_data->pc;

        inst.execute(context, frame);

        printf("pc:%d\n", pc);

        free(context);

        // stack is empty.
        if (thread->stack->top == NULL) {
            break;
        }
    }
}

void interpret(struct Method *main_method)
{
    struct Thread *thread = newThread();
    struct Frame *frame = newFrame(thread, main_method);
    pushFrame(frame, thread);

    loop(thread);
}
