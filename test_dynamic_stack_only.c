#include <assert.h>
#include <stdio.h>
#include "stack.h"

static void test_dynamic_stack_init_is_empty_is_full(void)
{
    StackDynamic stack = {0};
    stack.before = NULL;

    initDynamicStack(&stack);
    assert(isDynamicStackEmpty(&stack) == true);
    assert(isDynamicStackFull(&stack) == false);
    assert(peekDynamicStack(&stack) == -1);
}

static void test_dynamic_stack_push_pop_peek(void)
{
    StackDynamic stack = {0};
    stack.before = NULL;
    initDynamicStack(&stack);

    assert(pushDynamicStack(&stack, 10) == true);
    assert(peekDynamicStack(&stack) == 10);

    assert(pushDynamicStack(&stack, 20) == true);
    assert(peekDynamicStack(&stack) == 20);

    assert(popDynamicStack(&stack) == 20);
    assert(peekDynamicStack(&stack) == 10);

    assert(popDynamicStack(&stack) == 10);
    assert(isDynamicStackEmpty(&stack) == true);
    assert(popDynamicStack(&stack) == -1);
}

int main(void)
{
    test_dynamic_stack_init_is_empty_is_full();
    test_dynamic_stack_push_pop_peek();
    printf("All dynamic stack tests passed!\n");
    return 0;
}
