//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_INTERPRETER_H
#define TOYJVM_INTERPRETER_H

#include "type.h"
#include "rtda.h"
#include "bytecode.h"

void interpret(struct Method *main);

void invokeMethod(struct Frame *invokerFrame, struct Method *method);


#endif //TOYJVM_INTERPRETER_H
