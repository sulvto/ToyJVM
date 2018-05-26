//
// Created by sulvto on 18-4-30.
//

#ifndef TOYJVM_RTDA_H
#define TOYJVM_RTDA_H

#include "type.h"

#define Slot_T Slot
typedef struct Slot_T *Slot_T;

#define Slots_T Slots
typedef struct Slots_T *Slots_T;

#define Object_T Object
typedef struct Object_T *Object_T;

#define OperandStack_T OperandStack
typedef struct OperandStack_T *OperandStack_T;

#define Frame_T Frame
typedef struct Frame_T *Frame_T;

#define Stack_T Stack
typedef struct Stack_T *Stack_T;

#define Thread_T Thread
typedef struct Thread_T *Thread_T;

extern Slots_T newSlots(const unsigned int max);

Thread_T newThread();

Frame_T newFrame(Thread_T, u4 , u4, void *);

void Thread_pushFrame(Thread_T, Frame_T);

Frame_T Thread_popFrame(Thread_T);

Frame_T Thread_topFrame(Thread_T);

Frame_T Thread_currentFrame(Thread_T);

Object getRefFromStackTop(OperandStack_T stack, u4 i);

void pushInt(const int, OperandStack_T);

void pushLong(const long, OperandStack_T);

void pushFloat(const float, OperandStack_T);

void pushDouble(const double, OperandStack_T);

void pushRef(const Object_T, OperandStack_T);

void pushSlot(const Slot_T slot, OperandStack_T);

int popInt(OperandStack_T);

long popLong(OperandStack_T);

float popFloat(OperandStack_T);

double popDouble(OperandStack_T);

Object_T popRef(OperandStack_T);

Slot_T popSlot(OperandStack_T);

void setInt(const unsigned int index, int value, Slots_T slots);

void setLong(const unsigned int index, long value, Slots_T slots);

void setFloat(const unsigned int index, float value, Slots_T slots);

void setDouble(const unsigned int index, double value, Slots_T slots);

void setRef(const unsigned int index, Object_T value, const Slots_T slots);

void setSlot(const unsigned int index, Slot_T value, const Slots_T slots);

int getInt(const unsigned int index, Slots_T slots);

long getLong(const unsigned int index, Slots_T slots);

float getFloat(const unsigned int index, Slots_T slots);

double getDouble(const unsigned int index, Slots_T slots);

Object_T getRef(const unsigned int index, Slots_T slots);

Slot_T getSlot(const unsigned int index, const Slots_T slots);


void Object_setInt(Object_T object, const unsigned int index, int value);

void Object_setLong(Object_T object, const unsigned int index, long value);

void Object_setFloat(Object_T object, const unsigned int index, float value);

void Object_setDouble(Object_T object, const unsigned int index, double value);

void Object_setRef(Object_T object, const unsigned int index, Object_T value);

void Object_setClass(Object_T, void*);

void *Object_getClass(Object_T);

void Object_setFields(Object_T _this, void *fields);

void *Object_getFields(Object_T _this);

OperandStack_T OperandStack_new(const unsigned int max);

void OperandStack_clear(OperandStack_T);

void Frame_pushInt(Frame_T frame, const int);

void Frame_pushLong(Frame_T frame, const long);

void Frame_pushFloat(Frame_T frame, const float);

void Frame_pushDouble(Frame_T frame, const double);

void Frame_pushRef(Frame_T frame, const Object_T);

void Frame_pushSlot(Frame_T frame, const Slot_T slot);

int Frame_popInt(Frame_T frame);

long Frame_popLong(Frame_T frame);

float Frame_popFloat(Frame_T frame);

double Frame_popDouble(Frame_T frame);

Object_T Frame_popRef(Frame_T frame);

Slot_T Frame_popSlot(Frame_T frame);

void Frame_setInt(Frame_T frame, const unsigned int index, int value);

void Frame_setLong(Frame_T frame, const unsigned int index, long value);

void Frame_setFloat(Frame_T frame, const unsigned int index, float value);

void Frame_setDouble(Frame_T frame, const unsigned int index, double value);

void Frame_setRef(Frame_T frame, const unsigned int index, Object_T value);

void Frame_setSlot(Frame_T frame, const unsigned int index, Slot_T value);

int Frame_getInt(Frame_T frame, const unsigned int index);

long Frame_getLong(Frame_T frame, const unsigned int index);

float Frame_getFloat(Frame_T frame, const unsigned int index);

double Frame_getDouble(Frame_T frame, const unsigned int index);

Object_T Frame_getRef(Frame_T frame, const unsigned int index);

Slot_T Frame_getSlot(Frame_T frame, const unsigned int index);

Thread_T Frame_thread(Frame_T);

OperandStack_T Frame_stack(Frame_T _this);

void Frame_revertNextPC(Frame_T);

void *Frame_method(Frame_T);

Slots Frame_localVars(Frame_T);

void Frame_setNextPC(Frame_T, int);

int Frame_getNextPC(Frame_T);

int Thread_isStackEmpty(Thread_T);

void Thread_setPc(Thread_T, int);

int Thread_getPc(Thread_T);

#undef Slot_T
#undef Slots_T
#undef Object_T
#undef OperandStack_T
#undef Frame_T
#undef Stack_T
#undef Thread_T

#endif //TOYJVM_RTDA_H
