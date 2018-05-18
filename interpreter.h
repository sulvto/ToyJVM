//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_INTERPRETER_H
#define TOYJVM_INTERPRETER_H

#include "type.h"
#include "rtda.h"
#include "bytecode.h"
#include "class.h"

void interpret(Method main);

void invokeMethod(Frame invokerFrame, Method method);


#endif //TOYJVM_INTERPRETER_H
