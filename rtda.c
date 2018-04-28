//
// Run-Time Data Area
//
// Created by sulvto on 18-4-28.
//


struct Object {
    // TODO
};

struct Slot {
    int             num;
    struct Object   *ref;
};

typedef struct Slot* LocalVars;

struct OperandStack {
    unsigned int size;
    struct Slot *slot;
};

struct Frame {
    struct Frame        *next;
    struct Slot         *localVars;
    struct OperandStack *operand_stack;
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

LocalVars *newLocalVars(const unsigned int max)
{
    struct Slot *slot = (struct Slot *) malloc(sizeof(struct Slot) * max);
    return slot;
}

struct OperandStack *newOperandStack(const unsigned int max)
{
    struct OperandStack *operand_stack = (struct OperandStack *) malloc(sizeof(struct OperandStack));
    operand_stack->size = max;
    operand_stack->slot = (struct Slot *) malloc(sizeof(struct Slot) * max);
    return operand_stack;
}

struct Frame *newFrame(const unsigned int maxLocalVars, const unsigned int maxStack)
{
    struct Frame *frame = (struct Frame *) malloc(sizeof(struct Frame));
    frame->localVars = newLocalVars(maxLocalVars);
    frame->operand_stack = newOperandStack(maxStack);
    return frame;
}


void pushStack(struct Frame *frame, struct Stack *stack)
{
    // TODO
}

struct Stack *popStack(struct Stack *stack)
{
    // TODO
}

struct Stack *topStack(struct Stack *stack)
{
    // TODO
}

void pushFrame(struct Frame *frame, struct Thread *thread)
{
    // TODO
}

struct Frame *popFrame(struct Thread *thread)
{
    // TODO
}

void pushInt(const int value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value;
}

void pushLong(const long value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value;
    operandStack->slot[operandStack->size++].num = value >> 32;
}

void pushFloat(const float value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value;
}

void pushDouble(const double value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].num = value;
    operandStack->slot[operandStack->size++].num = value >> 32;
}

void pushRef(const struct Object *value, struct OperandStack *operandStack)
{
    operandStack->slot[operandStack->size++].ref = value;
}

int popInt(struct OperandStack *operandStack)
{
    return operandStack->slot[operandStack->size--].num;
}

long popLong(struct OperandStack *operandStack)
{
    long l = operandStack->slot[operandStack->size--].num;
    l = l << 32;
    l &= operandStack->slot[operandStack->size--].num;
    return l;
}

float popFloat(struct OperandStack *operandStack)
{
    return operandStack->slot[operandStack->size--].num;
}

double popDouble(struct OperandStack *operandStack)
{
    double d = operandStack->slot[operandStack->size--].num;
    d = d << 32;
    d &= operandStack->slot[operandStack->size--].num;
    return d;
}


struct Object *popRef(struct OperandStack *operandStack)
{
    return operandStack->slot[operandStack->size--].ref;
}


void setInt(const unsigned int index, int value, LocalVars *localVars)
{
    localVars[index]->num = value;
}

void setLong(const unsigned int index, long value, LocalVars *localVars)
{
    localVars[index]->num = value;
    localVars[index + 1]->num = value >> 32;
}

void setFloat(const unsigned int index, float value, LocalVars *localVars)
{
    localVars[index]->num = value;
}

void setDouble(const unsigned int index, double value, LocalVars *localVars)
{
    localVars[index]->num = value;
    localVars[index + 1]->num = value >> 32;
}

void setRef(const unsigned int index, struct Object *value, LocalVars *localVars)
{
    localVars[index]->ref = value;

}

int getInt(const unsigned int index, LocalVars *localVars)
{
    return localVars[index]->num;
}

long getLong(const unsigned int index, LocalVars *localVars)
{
    long result = localVars[index++]->num;
    result = result << 32;
    result &= localVars[index]->num;
    return result;
}

float getFloat(const unsigned int index, LocalVars *localVars)
{
    return (float) localVars[index]->num;
}

double getDouble(const unsigned int index, LocalVars *localVars)
{
    double result = localVars[index++]->num;
    result = result << 32;
    result &= localVars[index]->num;
    return result;
}

struct Object *getRef(const unsigned int index, LocalVars *localVars)
{
    return localVars[index]->ref;
}

void testLocalVars(LocalVars localVars) {
    setInt(0, 100, localVars);
    setInt(1, -100, localVars);
    setLong(2, 2997924580, localVars);
    setLong(4, -2997924580, localVars);
    setFloat(6, 3.1415926, localVars);
    setDouble(7, 2.71828182845, localVars);
    setRef(9, NULL, localVars);

    print(getInt(0, localVars));
    print(getInt(1, localVars));
    print(getLong(2, localVars));
    print(getLong(4, localVars));
    print(getFloat(6, localVars));
    print(getDouble(7, localVars));
    print(getRef(9, localVars));
}

void testOperandStack(struct OperandStack *operandStack)
{
    pushInt(100, operandStack);
    pushInt(-100, operandStack);
    pushLong(2997924580, operandStack);
    pushLong(-2997924580, operandStack);
    pushFloat(3.1415926, operandStack);
    pushDouble(2.71828182845, operandStack);
    pushRef(NULL, operandStack);

    print(popInt(operandStack));
    print(popInt(operandStack));
    print(popLong(operandStack));
    print(popLong(operandStack));
    print(popFloat(operandStack));
    print(popDouble(operandStack));
}


int main()
{
    struct Frame *frame = newFrame(100, 100);
    LocalVars localVars = &frame->localVars;
    testLocalVars(localVars);
    testOperandStack(localVars);
}