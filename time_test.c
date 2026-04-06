#include "deter.h"
#include "deq_and_stack.h"

#define NUMBER_FOR_TEST 5400000

void for_sstack(StackStatic *sstack) {
    clock_t start = clock();
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        pushStack(sstack, i);
    }
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        popStack(sstack);
    }
    clock_t end = clock();
    printf("Время для статического стека: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void for_dstack(StackDynamic *dstack) {
    clock_t start = clock();
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        pushStack(dstack, i);
    }
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        popStack(dstack);
    }
    clock_t end = clock();
    printf("Время для динамического стека: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void for_sdeq(DequeStatic *sdeque) {
    clock_t start = clock();
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        pushDequeBack(sdeque, i);
    }
    for(int i = 0; i < NUMBER_FOR_TEST; i++) {
        popDequeBack(sdeque);
    }
    clock_t end = clock();
    printf("Время для статического дека: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void for_ddeq(DequeDynamic *ddeque) {
    clock_t start = clock();
    for(int i = 1; i < NUMBER_FOR_TEST; i++) {
        if(!pushDequeBack(ddeque, i))
        {
            destroyDeque(ddeque);
        }
    }
    for(int i = 1; i < NUMBER_FOR_TEST; i++) {
        popDequeBack(ddeque);
    }
    clock_t end = clock();
    printf("Время для динамического дека: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    DequeStatic sdeque;
    DequeDynamic ddeque = {0};
    StackDynamic dstack;
    StackStatic sstack;
    initStack(&sstack);
    initStack(&dstack);
    deque_static_init(&sdeque, 1500000);
    DequeDynamic deqInit = deque_dynamic_init(&ddeque);
    printf("КОЛИЧЕСТВО ТЕСТОВ %lld\n", NUMBER_FOR_TEST);
    for_sstack(&sstack);
    for_dstack(&dstack);
    for_sdeq(&sdeque);
    for_ddeq(&deqInit);

    return 0;
}