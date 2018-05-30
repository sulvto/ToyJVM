//
// Run-Time Data Area
//
// Created by sulvto on 18-4-28.
//

#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "rtda.h"
#include "type.h"

#define Slot_T Slot
#define Slots_T Slots
#define Object_T Object
#define OperandStack_T OperandStack
#define Frame_T Frame
#define Stack_T Stack
#define Thread_T Thread


struct Slot_T {
    int             num;
    Object_T   ref;
};


struct Slots_T {
    unsigned int size;
    unsigned int max;
    Slot_T *value;
};


struct Object_T {
    void *_class;
    void *fields;
};


struct OperandStack_T {
    unsigned int size;
    Slot_T *slot;
};

struct Frame_T {
    Frame_T                 next;
    Slots_T                 localVars;
    OperandStack_T          operand_stack;
    int                     nextPC;
    Thread_T                thread;
    void                    *method;
};

struct Stack_T {
    unsigned int max_size;
    unsigned int size;
    Frame_T top;
};

struct Thread_T {
    int          pc;
    Stack_T stack;
};

static Stack_T Stack_new(const unsigned int size) {
    Stack_T stack = (Stack_T) malloc(sizeof(struct Stack));
    stack->max_size = size;
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

Thread_T newThread() {
    Thread_T thread = (Thread_T) malloc(sizeof(struct Thread));
    thread->stack = Stack_new(1024);
    thread->pc = 0;
    return thread;
}

Slots_T Slots_new(const unsigned int max) {
    Slots_T slots = (Slots_T) malloc(sizeof(struct Slots));
    slots->size = 0;
    slots->max = max;
    slots->value = (Slot_T*) malloc(sizeof(struct Slot) * max);
    return slots;
}

OperandStack_T OperandStack_new(const unsigned int max) {
    OperandStack_T operand_stack = (OperandStack_T)malloc(sizeof(struct OperandStack));
    operand_stack->size = 0;
    operand_stack->slot = (Slot_T*) malloc(sizeof(struct Slot) * max);
    return operand_stack;
}

void OperandStack_clear(OperandStack_T _this) {
    for (int i = 0; i < _this->size; ++i) {
        _this->slot[i] = NULL;
    }
    _this->size = 0;
}


Object getRefFromStackTop(OperandStack_T stack, u4 i) {
    if (stack->size == 0) {
        return NULL;
    }
    return stack->slot[stack->size - 1 - i]->ref;
}

Frame_T newFrame(Thread_T thread, u4 max_locals, u4 max_stack, void *method) {
    Frame_T frame = (Frame_T) malloc(sizeof(struct Frame));
    frame->localVars = Slots_new(max_locals);
    frame->operand_stack = OperandStack_new(max_stack);
    frame->thread = thread;
    frame->method = method;
    return frame;
}

void Thread_pushFrame(Thread_T _this, Frame_T frame) {
    Stack_T stack = _this->stack;

    if (stack->size >= stack->max_size) {
        // TODO
        printf("StackOverflowError!");
    }

    if (stack->top != NULL) {
        frame->next = stack->top;
    }
    stack->top = frame;
    stack->size++;
}

Frame_T Thread_popFrame(Thread_T _this) {
    if (_this->stack->top == NULL) {
        // TODO
        printf("jvm stack is empty!\n");
    }

    Frame_T top = _this->stack->top;
    _this->stack->top = top->next;
    _this->stack->size--;
    top->next = NULL;

    return top;
}

Frame_T Thread_topFrame(Thread_T _this) {
    if (_this->stack->top == NULL) {
        // TODO
        printf("jvm stack is empty!\n");
    }

    return _this->stack->top;
}

Frame_T Thread_currentFrame(Thread_T _this) {
    // TODO
    printf("Thread_currentFrame Unimplemented!\n");
    exit(1);
}

int Thread_empty(Thread_T _this) {
    return _this->stack->size == 0;
}

int Thread_isStackEmpty(Thread_T _this) {
    return _this->stack->top == NULL;
}

void Thread_setPc(Thread_T _this, int pc) {
    _this->pc = pc;
}

int Thread_getPc(Thread_T _this) {
    return _this->pc;
}

void Frame_setNextPC(Frame_T frame, int pc) {
    frame->nextPC = pc;
}

int Frame_getNextPC(Frame_T frame) {
    return frame->nextPC;
}

void OperandStack_push(OperandStack_T operandStack) {
    operandStack->slot[operandStack->size] = malloc(sizeof(Slot_T));
}

void pushInt(const int value, OperandStack_T operandStack) {
    operandStack->slot[operandStack->size] = malloc(sizeof(Slot_T));
    operandStack->slot[operandStack->size++]->num = value;
}

void pushLong(const long value, OperandStack_T operandStack) {
    operandStack->slot[operandStack->size++]->num = value >> 16;
    operandStack->slot[operandStack->size++]->num = value & 65535L;
}

void pushFloat(const float value, OperandStack_T operandStack) {
    float *f = &(operandStack->slot[operandStack->size++]->num);
    *f = value;
}

void pushDouble(const double value, OperandStack_T operandStack) {
//    operandStack->slot[operandStack->size++].num = value;
//    operandStack->slot[operandStack->size++].num = value >> 32;
}

void pushRef(const Object_T value, OperandStack_T operandStack) {
    operandStack->slot[operandStack->size++]->ref = value;
}

void pushSlot(const Slot_T slot, OperandStack_T operandStack) {
    OperandStack_push(operandStack);
    struct Slot *target = operandStack->slot[operandStack->size++];
    target->num = slot->num;
    target->ref = slot->ref;
}

int popInt(OperandStack_T operandStack) {
    return operandStack->slot[--operandStack->size]->num;
}

long popLong(OperandStack_T operandStack) {
    long low = operandStack->slot[--operandStack->size]->num;
    int high = operandStack->slot[--operandStack->size]->num;
    high = high << 16;
    return (high | low);
}

float popFloat(OperandStack_T operandStack) {
    float *f = &(operandStack->slot[--operandStack->size]->num);
    return *f;
}

double popDouble(OperandStack_T operandStack) {
    // TODO
//    double d = operandStack->slot[--operandStack->size].num;
//    d = d << 32;
//    d &= operandStack->slot[--operandStack->size].num;
    return 0;
}

Object_T popRef(OperandStack_T operandStack) {
    return operandStack->slot[--operandStack->size]->ref;
}

Slot_T popSlot(OperandStack_T operandStack) {
    return operandStack->slot[--operandStack->size];
}

void setInt(const unsigned int index, int value, Slots_T slots) {
    slots->value[index] = malloc(sizeof(Slot_T));
    slots->value[index]->num = value;
}

void setLong(const unsigned int index, long value, Slots_T slots) {
//    int high = value >> 16;
//    int low = value & 65535;
    slots->value[index]->num = value >> 16;
    slots->value[index + 1]->num = value & 65535L;
}

void setFloat(const unsigned int index, float value, Slots_T slots) {
    float *f = &slots->value[index]->num;
    *f = value;
}

void setDouble(const unsigned int index, double value, Slots_T slots) {
    // TODO
//    slots[index]->num = value;
//    slots[index + 1]->num = value >> 32;
}

void setRef(const unsigned int index, Object_T value, const Slots_T slots) {
    slots->value[index]->ref = value;
}

void setSlot(const unsigned int index, Slot_T value, const Slots_T slots) {
    slots->value[index] = value;
}

int getInt(const unsigned int index, Slots slots) {
    return slots->value[index]->num;
}

long getLong(const unsigned int index, Slots slots) {
    long high = slots->value[index]->num;
    int low = slots->value[index + 1]->num;
    high = high << 16;
    return (high | low);
}

float getFloat(const unsigned int index, Slots slots) {
    float *f = &slots->value[index]->num;
    return *f;
}

double getDouble(const unsigned int index, Slots slots) {
//    double result = slots[index++]->num;
//    result = result << 32;
//    result &= slots[index]->num;
    return 0;
}

Object_T getRef(const unsigned int index, Slots slots) {
    return slots->value[index]->ref;
}

Slot_T getSlot(const unsigned int index, const Slots slots) {
    return slots->value[index];
}


void Object_setInt(Object_T object, const unsigned int index, int value) {
    setInt(index, value, object->fields);
}

void Object_setLong(Object_T object, const unsigned int index, long value) {
    setLong(index, value, object->fields);
}

void Object_setFloat(Object_T object, const unsigned int index, float value) {
    setFloat(index, value, object->fields);
}

void Object_setDouble(Object_T object, const unsigned int index, double value) {
    setDouble(index, value, object->fields);
}

void Object_setRef(Object_T object, const unsigned int index, Object_T value) {
    setRef(index, value, object->fields);
}

void Object_setClass(Object_T _this, void *_class) {
    _this->_class = _class;
}

void *Object_getClass(Object_T _this) {
    return _this->_class;
}

void Object_setFields(Object_T _this, void *fields) {
    _this->fields = fields;
}

void *Object_getFields(Object_T _this) {
    return _this->fields;
}


void Frame_pushInt(Frame_T frame, const int value) {
    pushInt(value, frame->operand_stack);
}

void Frame_pushLong(Frame_T frame, const long value) {
    pushLong(value, frame->operand_stack);
}

void Frame_pushFloat(Frame_T frame, const float value) {
    pushFloat(value, frame->operand_stack);
}

void Frame_pushDouble(Frame_T frame, const double value) {
    pushDouble(value, frame->operand_stack);
}

void Frame_pushRef(Frame_T frame, const Object_T value) {
    pushRef(value, frame->operand_stack);
}

void Frame_pushSlot(Frame_T frame, const Slot_T slot) {
    pushSlot(slot, frame->operand_stack);

}

int Frame_popInt(Frame_T frame) {
    return popInt(frame->operand_stack);
}

long Frame_popLong(Frame_T frame) {
    return popLong(frame->operand_stack);
}

float Frame_popFloat(Frame_T frame) {
    return popFloat(frame->operand_stack);
}

double Frame_popDouble(Frame_T frame) {
    return popDouble(frame->operand_stack);
}

Object_T Frame_popRef(Frame_T frame) {
    return popRef(frame->operand_stack);
}

Slot_T Frame_popSlot(Frame_T frame) {
    return popSlot(frame->operand_stack);
}


void Frame_setInt(Frame_T frame, const unsigned int index, int value) {
    setInt(index, value, frame->localVars);
}

void Frame_setLong(Frame_T frame, const unsigned int index, long value) {
    setLong(index, value, frame->localVars);
}

void Frame_setFloat(Frame_T frame, const unsigned int index, float value) {
    setFloat(index, value, frame->localVars);
}

void Frame_setDouble(Frame_T frame, const unsigned int index, double value) {
    setDouble(index, value, frame->localVars);
}

void Frame_setRef(Frame_T frame, const unsigned int index, Object_T value ) {
    setRef(index, value, frame->localVars);
}

void Frame_setSlot(Frame_T frame, const unsigned int index, Slot_T value ) {
    setSlot(index, value, frame->localVars);
}

int Frame_getInt(Frame_T frame, const unsigned int index) {
    return getInt(index, frame->localVars);
}

long Frame_getLong(Frame_T frame, const unsigned int index) {
    return getLong(index, frame->localVars);
}

float Frame_getFloat(Frame_T frame, const unsigned int index) {
    return getFloat(index, frame->localVars);
}

double Frame_getDouble(Frame_T frame, const unsigned int index) {
    return getDouble(index, frame->localVars);
}

Object_T Frame_getRef(Frame_T frame, const unsigned int index) {
    return getRef(index, frame->localVars);
}

Slot_T Frame_getSlot(Frame_T frame, const unsigned int index) {
    return getSlot(index, frame->localVars);
}

Thread_T Frame_thread(Frame_T _this) {
    return _this->thread;
}

void *Frame_method(Frame_T _this) {
    return _this->method;
}

OperandStack_T Frame_stack(Frame_T _this) {
    return _this->operand_stack;
}

void Frame_revertNextPC(Frame_T _this) {
    _this->nextPC = _this->thread->pc;
}

Slots Frame_localVars(Frame_T _this) {
    return _this->localVars;
}

void testLocalVars(struct Slots *localVars) {
    setInt(0, 100, localVars);
    setInt(1, -100, localVars);
    setLong(2, 2147483647, localVars);
    setLong(4, -2147483647, localVars);
    setFloat(6, 3.1415926, localVars);
//    setDouble(3, 2.71828182845, localVars);
    setRef(7, NULL, localVars);

    printf("%d\n", getInt(0, localVars));
    printf("%d\n", getInt(1, localVars));
    printf("%d\n", getLong(2, localVars));
    printf("%d\n", getLong(4, localVars));
    printf("%f\n", getFloat(6, localVars));
//    printf("%u\n", getDouble(7, localVars));
    printf("%u\n", getRef(7, localVars));
}

void testOperandStack(OperandStack operandStack) {
    pushInt(100, operandStack);
    pushInt(-100, operandStack);
    pushLong(2147483647, operandStack);
    pushLong(-2147483647, operandStack);
    pushFloat(3.1415926, operandStack);
//    pushDouble(2.71828182845, operandStack);
    pushRef(NULL, operandStack);

    printf("%u\n", popRef(operandStack));
//        printf("%u\n", popDouble(operandStack));
    printf("%f\n", popFloat(operandStack));
    printf("%d\n", popLong(operandStack));
    printf("%d\n", popLong(operandStack));
    printf("%d\n", popInt(operandStack));
    printf("%d\n", popInt(operandStack));

}


// int main()
// {
//     struct Frame *frame = newFrame(100, 100);
//     struct Slots *localVars = frame->localVars;
//     OperandStack operandStack = frame->operand_stack;
//     printf("testLocalVars \n");
//     testLocalVars(localVars);
//     printf("testLocalVars \n");
//     testOperandStack(operandStack);
// }