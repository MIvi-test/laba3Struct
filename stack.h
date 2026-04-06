#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define initStack(x) _Generic((x), StackStatic*: initStaticStack, StackDynamic*: initDynamicStack)(x)
#define isStackEmpty(x) _Generic((x), StackStatic*: isStaticStackEmpty, StackDynamic*: isDynamicStackEmpty)(x)
#define isStackFull(x) _Generic((x), StackStatic*: isStaticStackFull, StackDynamic*: isDynamicStackFull)(x)
#define pushStack(x,value) _Generic((x), StackStatic*: pushStaticStack, StackDynamic*: pushDynamicStack)(x, value)
#define popStack(x) _Generic((x), StackStatic*: popStaticStack, StackDynamic*: popDynamicStack)(x)
#define peekStack(x) _Generic((x), StackStatic*: peekStaticStack, StackDynamic*: peekDynamicStack)(x)
#define destroyStack(x) _Generic((x), StackStatic*: destroyStaticStack, StackDynamic*: destroyDynamicStack)(x)
#define sizeStack(x) _Generic((x), StackStatic*: sizeStaticStack, StackDynamic*: sizeDynamicStack)(x)
// #define searchStack(x) _Generic((x),StackStatic*: searchStaticStack, StackDynamic*: searchDynamicStack )

#define MAX_STATIC_STACK_SIZE 1000

typedef struct StackStatic_struct {
    int massive_static_stack[MAX_STATIC_STACK_SIZE];
    short exits_count;
} StackStatic;

typedef struct StackDynamic{
    int id;
    struct StackDynamic *before;
} StackDynamic;






void initStaticStack(StackStatic *stack);
bool isStaticStackEmpty(StackStatic *stack); 
bool isStaticStackFull(StackStatic *stack);
bool pushStaticStack(StackStatic *stack, int value);
int popStaticStack(StackStatic *stack);
int peekStaticStack(StackStatic *stack);
void destroyStaticStack(StackStatic *stack);
short sizeStaticStack(StackStatic *stack);

void initDynamicStack(StackDynamic *stack);
bool isDynamicStackEmpty(StackDynamic *stack);
bool isDynamicStackFull(StackDynamic *stack);
bool pushDynamicStack(StackDynamic *stack, int value);
int popDynamicStack(StackDynamic *stack);
int peekDynamicStack(StackDynamic *stack);
void destroyDynamicStack(StackDynamic *stack);
short sizeDynamicStack(StackDynamic *stack);
// void searchDynamicStack(StackStatic *stack);

#include "static_stack.c"
#include "dynamic_stack.c"

#endif








