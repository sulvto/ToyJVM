//
// Created by sulvto on 18-4-30.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "bytecode.h"
#include "rtda.h"
#include "class.h"
#include "interpreter.h"
#include "instruction.h"



void loop(Thread thread) {

    struct Bytecode *bytecode_data = (struct Bytecode *) malloc(sizeof(struct Bytecode));


    while (1) {
        // current frame
        Frame frame = Thread_topFrame(thread);

        int pc = Frame_getNextPC(frame);
        Thread_setPc(thread, pc);

        Method method = (Method)Frame_method(frame);
        reset(Method_code(method), pc, bytecode_data);
        u1 opcode = readBytecodeU1(bytecode_data);


        union Context *context = (union Context *) malloc(sizeof(union Context));

        struct Instruction inst = newInstruction(opcode);
        inst.fetchOperands(context, bytecode_data);
        Frame_setNextPC(frame, bytecode_data->pc);

        inst.execute(context, frame);

        printf("pc:%d\n", pc);

        free(context);

        // stack is empty.
        if (Thread_empty(thread)) {
            break;
        }
    }
}

void interpret(Method main_method) {
    Thread thread = newThread();
    Frame frame = newFrame(thread, Method_maxLocals(main_method), Method_maxStack(main_method), main_method);
    Thread_pushFrame(thread, frame);

    loop(thread);
}
