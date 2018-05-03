//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_RTDA_H
#define TOYJVM_RTDA_H

#include "class.h"

struct Object {
    struct Class *_class;
    u4          field_count;
    struct Slot *fields;
};

struct Slot {
    int             num;
    struct Object   *ref;
};

struct Slots {
    unsigned int size;
    unsigned int max;
    struct Slot *value;
};

struct OperandStack {
    unsigned int size;
    struct Slot *slot;
};

struct Frame {
    struct Frame        *next;
    struct Slots    *localVars;
    struct OperandStack *operand_stack;
    int                 nextPC;
    struct Thread       *thread;
    struct Method       *method;
};

struct Stack {
    unsigned int max_size;
    unsigned int size;
    struct Frame *top;
};

struct Thread {
    int          pc;
    struct Stack *stack;
};

struct Slots *newSlots(const unsigned int max);

struct Thread *newThread();

struct Frame *newFrame(const struct Thread *thread, const struct Method *method);

void pushFrame(struct Frame *frame, struct Thread *thread);

struct Frame *popFrame(struct Thread *thread);


void pushInt(const int, struct OperandStack *);

void pushLong(const long, struct OperandStack *);

void pushFloat(const float, struct OperandStack *);

void pushDouble(const double, struct OperandStack *);

void pushRef(const struct Object *, struct OperandStack *);

void pushSlot(const struct Slot slot, struct OperandStack *);

int popInt(struct OperandStack *);

long popLong(struct OperandStack *);

float popFloat(struct OperandStack *);

double popDouble(struct OperandStack *);

struct Object *popRef(struct OperandStack *);

struct Slot popSlot(struct OperandStack *);

void setInt(const unsigned int index, int value, struct Slots *localVars);

void setLong(const unsigned int index, long value, struct Slots *localVars);

void setFloat(const unsigned int index, float value, struct Slots *localVars);

void setDouble(const unsigned int index, double value, struct Slots *localVars);

void setRef(const unsigned int index, struct Object *value, const struct Slots *localVars);

int getInt(const unsigned int index, struct Slots *localVars);

long getLong(const unsigned int index, struct Slots *localVars);

float getFloat(const unsigned int index, struct Slots *localVars);

double getDouble(const unsigned int index, struct Slots *localVars);

struct Object *getRef(const unsigned int index, struct Slots *localVars);


#endif //TOYJVM_RTDA_H
