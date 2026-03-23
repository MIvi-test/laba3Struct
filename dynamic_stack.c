#ifndef DINAMIC_STACK_C
#define DINAMIC_STACK_C

#include "stack.h"


void initDynamicStack(StackDynamic *stack)
{
    stack->id = 0;
    stack->before = NULL;
}
bool isDynamicStackEmpty(StackDynamic *stack)
{
    return stack->before == NULL;
}
bool isDynamicStackFull(StackDynamic *stack)
{
    return false;
}
bool pushDynamicStack(StackDynamic *stack, int value)
{
    StackDynamic *new_stack = (StackDynamic *)malloc(sizeof(StackDynamic));
    if (new_stack == NULL)
    {
        return false;
    }
    new_stack->id = value;
    new_stack->before = stack;
    *stack = *new_stack;
    return true;
}
int popDynamicStack(StackDynamic *stack)
{
    if (isDynamicStackEmpty(stack))
    {
        return -1;
    }
    int value = stack->id;
    StackDynamic *new_stack = stack->before;
    free(stack);
    *stack = *new_stack;
    return value;
}
int peekDynamicStack(StackDynamic *stack)
{
    if (isDynamicStackEmpty(stack))
    {
        return -1;
    }
    return stack->id;
}
void destroyDynamicStack(StackDynamic *stack)
{
    while (stack != NULL)
    {
        StackDynamic *new_stack = stack->before;
        free(stack);
        stack = new_stack;
    }
}
short sizeDynamicStack(StackDynamic *stack)
{
    short size = 0;
    while (stack != NULL)
    {
        size++;
        stack = stack->before;
    }
    return size;
}
#endif