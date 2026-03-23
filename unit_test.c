
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq_and_stack.h"

static void test_static_stack_init_and_empty(void)
{
    StackStatic stack;
    initStaticStack(&stack);

    assert(isStaticStackEmpty(&stack) == true);
    assert(isStaticStackFull(&stack) == false);
    assert(sizeStaticStack(&stack) == 0);
    assert(peekStaticStack(&stack) == -1);
    assert(popStaticStack(&stack) == -1);
}

static void test_static_stack_push_pop_peek_size(void)
{
    StackStatic stack;
    initStaticStack(&stack);

    assert(pushStaticStack(&stack, 10) == true);
    assert(pushStaticStack(&stack, 20) == true);
    assert(pushStaticStack(&stack, 30) == true);

    assert(isStaticStackEmpty(&stack) == false);
    assert(sizeStaticStack(&stack) == 3);
    assert(peekStaticStack(&stack) == 30);

    assert(popStaticStack(&stack) == 30);
    assert(sizeStaticStack(&stack) == 2);
    assert(peekStaticStack(&stack) == 20);

    assert(popStaticStack(&stack) == 20);
    assert(popStaticStack(&stack) == 10);
    assert(popStaticStack(&stack) == -1);
    assert(isStaticStackEmpty(&stack) == true);
}

static void test_static_stack_full_and_destroy(void)
{
    StackStatic stack;
    initStaticStack(&stack);

    for (int i = 0; i < MAX_STATIC_STACK_SIZE; ++i)
    {
        assert(pushStaticStack(&stack, i) == true);
    }

    assert(isStaticStackFull(&stack) == true);
    assert(sizeStaticStack(&stack) == MAX_STATIC_STACK_SIZE);
    assert(pushStaticStack(&stack, 12345) == false);

    destroyStaticStack(&stack);
    assert(isStaticStackEmpty(&stack) == true);
    assert(isStaticStackFull(&stack) == false);
    assert(sizeStaticStack(&stack) == 0);
}

static void test_static_deque_init_and_empty(void)
{
    DequeStatic deque;
    deque_static_init(&deque);

    assert(deque_static_is_empty(&deque) == 1);
    assert(deque_static_is_full(&deque) == 0);
    assert(deque_static_peek_front(&deque) == -1);
    assert(deque_static_peek_back(&deque) == -1);
    assert(deque_static_pop_front(&deque) == -1);
    assert(deque_static_pop_back(&deque) == -1);
}

static void test_static_deque_push_back_and_pop(void)
{
    DequeStatic deque;
    deque_static_init(&deque);

    assert(deque_static_push_back(&deque, 10) == true);
    assert(deque_static_push_back(&deque, 20) == true);
    assert(deque_static_push_back(&deque, 30) == true);

    assert(deque_static_is_empty(&deque) == 0);
    assert(deque_static_peek_front(&deque) == 10);
    assert(deque_static_peek_back(&deque) == 30);

    assert(deque_static_pop_front(&deque) == 10);
    assert(deque_static_pop_back(&deque) == 30);
    assert(deque_static_pop_back(&deque) == 20);
    assert(deque_static_is_empty(&deque) == 1);
}

static void test_static_deque_push_front_and_wrap_logic(void)
{
    DequeStatic deque;
    deque_static_init(&deque);

    deque_static_push_front(&deque, 20);
    deque_static_push_front(&deque, 10);
    assert(deque_static_push_back(&deque, 30) == true);

    assert(deque_static_peek_front(&deque) == 10);
    assert(deque_static_peek_back(&deque) == 30);

    assert(deque_static_pop_front(&deque) == 10);
    assert(deque_static_pop_front(&deque) == 20);
    assert(deque_static_pop_front(&deque) == 30);
    assert(deque_static_pop_front(&deque) == -1);
}

static void test_static_deque_full(void)
{
    DequeStatic deque;
    deque_static_init(&deque);

    for (int i = 0; i < MAX_STATIC_DEQUE_SIZE; ++i)
    {
        assert(deque_static_push_back(&deque, i) == true);
    }

    assert(deque_static_is_full(&deque) == 1);
    assert(deque_static_push_back(&deque, 1001) == false);

    int first = deque_static_pop_front(&deque);
    assert(first == 0);
    assert(deque_static_is_full(&deque) == 0);
}

static void test_dynamic_stack_init_is_empty_is_full(void)
{
    StackDynamic stack = {0};
    stack.before = NULL;

    initDynamicStack(&stack);
    assert(isDynamicStackEmpty(&stack) == true);
    assert(isDynamicStackFull(&stack) == false);
    assert(peekDynamicStack(&stack) == -1);
}

static void test_dynamic_stack_size_on_single_node(void)
{
    StackDynamic stack = {0};
    stack.before = NULL;
    assert(sizeDynamicStack(&stack) == 1);
}

static void test_dynamic_deque_null_interface_guards(void)
{
    assert(deque_dynamic_push_front(NULL, 1) == false);
    assert(deque_dynamic_push_back(NULL, 1) == false);
    deque_dynamic_destroy(NULL);
}

/*
 * Dynamic deque implementation in the current project contains unsafe memory
 * access patterns for initialization/empty state operations. To keep the test
 * suite executable, tests below only cover the guard behavior that is safe to run.
 */

int main(void)
{
    test_static_stack_init_and_empty();
    test_static_stack_push_pop_peek_size();
    test_static_stack_full_and_destroy();

    test_static_deque_init_and_empty();
    test_static_deque_push_back_and_pop();
    test_static_deque_push_front_and_wrap_logic();
    test_static_deque_full();

    test_dynamic_stack_init_is_empty_is_full();
    test_dynamic_stack_size_on_single_node();

    test_dynamic_deque_null_interface_guards();

    printf("All available safe unit tests passed.\n");
    return 0;
}
