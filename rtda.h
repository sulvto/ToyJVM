//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_RTDA_H
#define TOYJVM_RTDA_H

struct Object {
    // TODO
};

struct Slot {
    int             num;
    struct Object   *ref;
};

struct LocalVars {
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
    struct LocalVars    *localVars;
    struct OperandStack *operand_stack;
    int                 nextPC;
    struct Thread       *thread;
};

struct Stack {
    unsigned int max_size;
    unsigned int size;
    struct Frame *frame;
};

struct Thread {
    int          pc;
    struct Stack *stack;
};

struct Thread *newThread();

struct Frame *newFrame(const unsigned int maxLocalVars, const unsigned int maxStack, struct Thread *thread);

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

void setInt(const unsigned int index, int value, struct LocalVars *localVars);

void setLong(const unsigned int index, long value, struct LocalVars *localVars);

void setFloat(const unsigned int index, float value, struct LocalVars *localVars);

void setDouble(const unsigned int index, double value, struct LocalVars *localVars);

void setRef(const unsigned int index, struct Object *value, const struct LocalVars *localVars);

int getInt(const unsigned int index, struct LocalVars *localVars);

long getLong(const unsigned int index, struct LocalVars *localVars);

float getFloat(const unsigned int index, struct LocalVars *localVars);

double getDouble(const unsigned int index, struct LocalVars *localVars);

struct Object *getRef(const unsigned int index, struct LocalVars *localVars);


#endif //TOYJVM_RTDA_H
