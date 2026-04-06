#ifndef DINAMIC_STACK_C
#define DINAMIC_STACK_C

#include "stack.h"


void initDynamicStack(StackDynamic *stack)
{
    if (stack != NULL)
    {
        stack->id = 0;
        stack->before = NULL;
    }
}
bool isDynamicStackEmpty(StackDynamic *stack)
{
    return stack == NULL || stack->before == NULL;
}
bool isDynamicStackFull(StackDynamic *stack)
{
    return false;
}
bool pushDynamicStack(StackDynamic *stack, int value)
{
    // For single-pointer interface, we can only push to non-empty positions
    // This limits dynamic stack usage - ideally should use pointer-to-pointer
    if (stack == NULL)
    {
        return false;
    }
    
    // Create new node and link it
    StackDynamic *new_node = (StackDynamic *)malloc(sizeof(StackDynamic));
    if (new_node == NULL)
    {
        return false;
    }
    
    // Insert between stack and its previous
    new_node->before = stack->before;
    new_node->id = value;
    stack->before = new_node;
    
    return true;
}
int popDynamicStack(StackDynamic *stack)
{
    if (isDynamicStackEmpty(stack) || stack->before == NULL)
    {
        return -1;
    }
    
    int value = stack->before->id;
    StackDynamic *temp = stack->before;
    stack->before = stack->before->before;
    free(temp);
    
    return value;
}
int peekDynamicStack(StackDynamic *stack)
{
    if (isDynamicStackEmpty(stack) || stack->before == NULL)
    {
        return -1;
    }
    return stack->before->id;
}
void destroyDynamicStack(StackDynamic *stack)
{
    if (stack == NULL)
    {
        return;
    }
    
    // Only free the dynamically allocated nodes (in the chain)
    // The root node itself may be on the stack, so don't free it
    while (stack->before != NULL)
    {
        StackDynamic *temp = stack->before;
        stack->before = stack->before->before;
        free(temp);
    }
}
short sizeDynamicStack(StackDynamic *stack)
{
    short size = 0;
    if (stack == NULL)
    {
        return 0;
    }
    // Count only the actual data nodes, not the sentinel root
    StackDynamic *current = stack->before;
    while (current != NULL)
    {
        size++;
        current = current->before;
    }
    return size;
}
#endif