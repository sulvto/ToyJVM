//
// Created by sulvto on 18-4-30.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "bytecode.h"
#include "classreader.h"
#include "rtda.h"
#include "instruction.h"
#include "interpreter.h"
#include "rtda.c"
#include "class.c"

void invokeMethod(Frame invoker_frame, Method method) {
    Thread thread = invoker_frame->thread;
    Frame new_frame = newFrame(thread, method);
    pushFrame(new_frame, thread);
    if (method->arg_count > 0) {
        for (int i = method->arg_count - 1; i >= 0; --i) {
            Slot slot = popSlot(invoker_frame->operand_stack);
            setSlot(i, slot, new_frame->localVars);
        }
    }
}


void loop(Thread thread) {

    struct Bytecode *bytecode_data = (struct Bytecode *) malloc(sizeof(struct Bytecode));


    while (1) {
        // current frame
        Frame frame = topFrame(thread);

        int pc = frame->nextPC;
        thread->pc = pc;

        reset(((Method)Frame_method(frame))->code, pc, bytecode_data);
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

void interpret(Method main_method) {
    Thread thread = newThread();
    Frame frame = newFrame(thread, main_method);
    pushFrame(frame, thread);

    loop(thread);
}
