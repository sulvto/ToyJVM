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
    struct Object   *object;
};

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

OperandStack newOperandStack(const unsigned int max)
{
    OperandStack operand_stack;
    operand_stack.size = max;
    operand_stack.slot = (struct Slot *) malloc(sizeof(struct Slot) * max);
    return operand_stack;
}


void pushStack(Frame *frame, Stack *stack)
{
    // TODO
}

Stack *popStack(Stack *stack)
{
    // TODO
}

Stack *topStack(Stack *stack)
{
    // TODO
}

void pushFrame(Frame *frame, Thread *thread)
{
    // TODO
}

Frame *popFrame(Thread *thread)
{
    // TODO
}
