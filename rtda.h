//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_RTDA_H
#define TOYJVM_RTDA_H

#include "class.h"

struct Object {
    struct Class *_class;
    struct Slots *fields;
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

void setInt(const unsigned int index, int value, struct Slots *slots);

void setLong(const unsigned int index, long value, struct Slots *slots);

void setFloat(const unsigned int index, float value, struct Slots *slots);

void setDouble(const unsigned int index, double value, struct Slots *slots);

void setRef(const unsigned int index, struct Object *value, const struct Slots *slots);

void setSlot(const unsigned int index, struct Slot *value, const struct Slots *slots);

int getInt(const unsigned int index, struct Slots *slots);

long getLong(const unsigned int index, struct Slots *slots);

float getFloat(const unsigned int index, struct Slots *slots);

double getDouble(const unsigned int index, struct Slots *slots);

struct Object *getRef(const unsigned int index, struct Slots *slots);

struct Slot getSlot(const unsigned int index, const struct Slots *slots);


#endif //TOYJVM_RTDA_H
