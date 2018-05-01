//
// Run-Time Data Area
//
// Created by sulvto on 18-4-28.
//

#include <stddef.h>
#include "rtda.h"

struct Stack *newStack(const unsigned int size)
{
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->max_size = size;
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

struct Thread *newThread()
{
    struct Thread *thread = (struct Thread *) malloc(sizeof(struct Thread));
    thread->stack = newStack(1024);
    thread->pc = 0;
    return thread;
}

struct LocalVars *newLocalVars(const unsigned int max)
{
    struct LocalVars *localVars = (struct LocalVars *) malloc(sizeof(struct LocalVars));
    localVars->size = 0;
    localVars->max = max;
    localVars->value = (struct Slot *) malloc(sizeof(struct Slot) * max);
    return localVars;
}

struct OperandStack *newOperandStack(const unsigned int max)
{
    struct OperandStack *operand_stack = (struct OperandStack *) malloc(sizeof(struct OperandStack));
    operand_stack->size = 0;
    operand_stack->slot = (struct Slot *) malloc(sizeof(struct Slot) * max);
    return operand_stack;
}

struct Frame *newFrame(const unsigned int maxLocalVars, const unsigned int maxStack, struct Thread *thread)
{
    struct Frame *frame = (struct Frame *) malloc(sizeof(struct Frame));
    frame->localVars = newLocalVars(maxLocalVars);
    frame->operand_stack = newOperandStack(maxStack);
    frame->thread = thread;
    return frame;
}

void pushFrame(struct Frame *frame, struct Thread *thread)
{
    struct Stack *stack = thread->stack;

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

struct Frame *popFrame(struct Thread *thread)
{
    if (thread->stack->top == NULL) {
        // TODO
        printf("jvm stack is empty!\n");
    }

    struct Frame *top = thread->stack->top;
    thread->stack->top = top->next;
    thread->stack->size--;
    top->next = NULL;

    return top;
}

void pushInt(const int value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value;
}

void pushLong(const long value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value >> 16;
    operandStack->slot[operandStack->size++].num = value & 65535L;
}

void pushFloat(const float value, struct OperandStack *operandStack)
{
    float *f = &operandStack->slot[operandStack->size++].num;
    *f = value;
}

void pushDouble(const double value, struct OperandStack *operandStack)
{
//    operandStack->slot[operandStack->size++].num = value;
//    operandStack->slot[operandStack->size++].num = value >> 32;
}

void pushRef(const struct Object *value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].ref = value;
}

void pushSlot(const struct Slot slot, struct OperandStack *operandStack)
{
    struct Slot *target = &operandStack->slot[operandStack->size++];
    target->num = slot.num;
    target->ref = slot.ref;
}

int popInt(struct OperandStack *operandStack)
{
    return operandStack->slot[--operandStack->size].num;
}

long popLong(struct OperandStack *operandStack)
{
    long low = operandStack->slot[--operandStack->size].num;
    int high = operandStack->slot[--operandStack->size].num;
    high = high << 16;
    return (high | low);
}

float popFloat(struct OperandStack *operandStack)
{
    float *f =  &operandStack->slot[--operandStack->size].num;
    return *f;
}

double popDouble(struct OperandStack *operandStack)
{
    // TODO
//    double d = operandStack->slot[--operandStack->size].num;
//    d = d << 32;
//    d &= operandStack->slot[--operandStack->size].num;
    return 0;
}

struct Object *popRef(struct OperandStack *operandStack)
{
    return operandStack->slot[--operandStack->size].ref;
}

struct Slot popSlot(struct OperandStack *operandStack)
{
    return operandStack->slot[--operandStack->size];
}

void setInt(const unsigned int index, int value, struct LocalVars *localVars)
{
    localVars->value[index].num = value;
}

void setLong(const unsigned int index, long value, struct LocalVars *localVars)
{
//    int high = value >> 16;
//    int low = value & 65535;
    localVars->value[index].num = value >> 16;
    localVars->value[index + 1].num = value & 65535L;
}

void setFloat(const unsigned int index, float value, struct LocalVars *localVars)
{
    float *f = &localVars->value[index].num;
    *f = value;
}

void setDouble(const unsigned int index, double value, struct LocalVars *localVars)
{
    // TODO
//    localVars[index]->num = value;
//    localVars[index + 1]->num = value >> 32;
}

void setRef(const unsigned int index, struct Object *value, const struct LocalVars *localVars)
{
    localVars->value[index].ref = value;
}

int getInt(const unsigned int index, struct LocalVars *localVars)
{
    return localVars->value[index].num;
}

long getLong(const unsigned int index, struct LocalVars *localVars)
{
    long high = localVars->value[index].num;
    int low = localVars->value[index + 1].num;
    high = high << 16;
    return (high | low);
}

float getFloat(const unsigned int index, struct LocalVars *localVars)
{
    float *f = &localVars->value[index].num;
    return *f;
}

double getDouble(const unsigned int index, struct LocalVars *localVars)
{
//    double result = localVars[index++]->num;
//    result = result << 32;
//    result &= localVars[index]->num;
    return 0;
}

struct Object *getRef(const unsigned int index, struct LocalVars *localVars)
{
    return localVars->value[index].ref;
}

void testLocalVars(struct LocalVars *localVars) {
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

void testOperandStack(struct OperandStack *operandStack)
{
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
//     struct LocalVars *localVars = frame->localVars;
//     struct OperandStack *operandStack = frame->operand_stack;
//     printf("testLocalVars \n");
//     testLocalVars(localVars);
//     printf("testLocalVars \n");
//     testOperandStack(operandStack);
// }