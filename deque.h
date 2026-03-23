#ifndef DEQUE_H
#define DEQUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// #define initDeque(x) _Generic((x), DequeStatic*: deque_static_init, DequeDynamic*: deque_dynamic_init)
#define isDequeEmpty(x) _Generic((x), DequeStatic*: deque_static_is_empty, DequeDynamic*: deque_dynamic_is_empty)
#define isDequeFull(x) _Generic((x), DequeStatic*: deque_static_is_full)
#define pushDequeFront(x, value) _Generic((x), DequeStatic*: deque_static_push_front, DequeDynamic*: deque_dynamic_push_front)(x, value)
#define pushDequeBack(x, value) _Generic((x), DequeStatic*: deque_static_push_back, DequeDynamic*: deque_dynamic_push_back)(x, value)
#define popDequeFront(x) _Generic((x), DequeStatic*: deque_static_pop_front, DequeDynamic*: deque_dynamic_pop_front)(x)
#define popDequeBack(x) _Generic((x), DequeStatic*: deque_static_pop_back, DequeDynamic*: deque_dynamic_pop_back)(x)
#define peekDequeFront(x) _Generic((x), DequeStatic*: deque_static_peek_front, DequeDynamic*: deque_dynamic_peek_front)(x)
#define peekDequeBack(x) _Generic((x), DequeStatic*: deque_static_peek_back, DequeDynamic*: deque_dynamic_peek_back)(x)
#define destroyDeque(x) _Generic((x), DequeStatic*: deque_static_destroy, DequeDynamic*: deque_dynamic_destroy)



typedef struct DequeDynamiс {
    struct DequeDynamiс *front;
    struct DequeDynamiс *back;
    int id;
}DequeDynamic;

typedef struct  DequeStatic {
    int *massive_static_deque;
    int head_index;
    int tail_index;
    int capacity;
}DequeStatic;


// Для DequeStatic
bool deque_static_init(DequeStatic* deque, int capacity);
void deque_static_destroy(DequeStatic* deque);
void deque_static_push_front(DequeStatic* deque, int value);
bool deque_static_push_back(DequeStatic* deque, int value);
int deque_static_pop_front(DequeStatic* deque);
int deque_static_pop_back(DequeStatic* deque);
bool deque_static_is_empty(DequeStatic* deque);
bool deque_static_is_full(DequeStatic* deque);
int deque_static_peek_front(DequeStatic* deque);
int deque_static_peek_back(DequeStatic* deque);

// Для DequeDynamic
void deque_dynamic_create(DequeDynamic* deque);
void deque_dynamic_destroy(DequeDynamic* deque);
bool deque_dynamic_push_front(DequeDynamic* deque, int value);
bool deque_dynamic_push_back(DequeDynamic* deque, int value);
int deque_dynamic_pop_front(DequeDynamic* deque);
int deque_dynamic_pop_back(DequeDynamic* deque);
bool deque_dynamic_is_empty(DequeDynamic* deque);
int deque_dynamic_peek_front(DequeDynamic* deque);
int deque_dynamic_peek_back(DequeDynamic* deque);



#include "static_deque.c"
#include "dynamic_deque.c"

#endif