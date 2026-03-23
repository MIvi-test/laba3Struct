#ifndef STACK_TEST_C
#define STACK_TEST_C

#include "stack.h"


void initStaticStack(StackStatic *stack)
{
    memset(stack->massive_static_stack, 0, sizeof(stack->massive_static_stack));
    stack->exits_count = 0;
}
bool isStaticStackEmpty(StackStatic *stack)
{
    return stack->exits_count == 0;
}
bool isStaticStackFull(StackStatic *stack)
{
    return stack->exits_count == MAX_STATIC_STACK_SIZE;
}

bool pushStaticStack(StackStatic *stack, int value)
{
    if (isStaticStackFull(stack))
    {
        return false;
    }
    stack->massive_static_stack[stack->exits_count] = value;
    stack->exits_count++;
    return true;
}
int popStaticStack(StackStatic *stack)
{
    if (isStaticStackEmpty(stack))
    {
        return -1;
    }
    int value = stack->massive_static_stack[stack->exits_count - 1];
    stack->massive_static_stack[stack->exits_count - 1] = 0;
    stack->exits_count--;
    return value;
}
int peekStaticStack(StackStatic *stack)
{
    if (isStaticStackEmpty(stack))
    {
        return -1;
    }
    return stack->massive_static_stack[stack->exits_count - 1];
}
void destroyStaticStack(StackStatic *stack)
{
    memset(stack->massive_static_stack, 0, sizeof(stack->massive_static_stack));
    stack->exits_count = 0;
}
short sizeStaticStack(StackStatic *stack)
{
    return stack->exits_count;
}

#endif