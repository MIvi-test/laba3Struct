#ifndef STATIC_DEQUE_C
#define STATIC_DEQUE_C
#include "deque.h"

bool deque_static_init(DequeStatic* deque, int capacity)
{

    deque->tail_index = -1;
    deque->head_index = -1;
    deque->capacity = capacity;
    int *data = (int*)calloc(capacity, sizeof(int));
    if(!data)
    {
        deque->massive_static_deque = NULL;
        return false;
    }
    deque->massive_static_deque = data;
    return true;
}

void deque_static_destroy(DequeStatic* deque)
{
    free(deque->massive_static_deque);
    return;
}

bool deque_static_is_empty(DequeStatic* deque)
{
    return (deque == NULL || deque->head_index == -1);
}

bool deque_static_is_full(DequeStatic* deque)
{
    if (deque == NULL)
    {
        return 0;
    }
    if (deque_static_is_empty(deque))
    {
        return 0;
    }
    return ((deque->tail_index + 1) % deque->capacity) == deque->head_index;
}

void deque_static_push_front(DequeStatic* deque, int value) // head
{
    if (deque == NULL || deque_static_is_full(deque))
    {
        return;
    }

    if (deque_static_is_empty(deque))
    {
        deque->head_index = 0;
        deque->tail_index = 0;
        deque->massive_static_deque[0] = value;
        return;
    }
    
    if(deque->head_index == 0)
    {
        int z = deque->massive_static_deque[0];
        int v;
        for(int i = 0; i <deque->capacity - 1; i++)
        {
            v = deque->massive_static_deque[i+1];
            deque->massive_static_deque[i+1] = z;
            z = v;
        }
    }
    deque->massive_static_deque[0] = value;
    deque->tail_index+=1;
}

bool deque_static_push_back(DequeStatic* deque, int value) //tail
{
    if (deque == NULL || deque_static_is_full(deque))
    {
        return false;
    }

    if (deque_static_is_empty(deque))
    {
        deque->head_index = 0;
        deque->tail_index = 0;
        deque->massive_static_deque[0] = value;
        return true;
    }

    if(deque->tail_index == deque->capacity-1)
    {
        for(int i = 0; i < deque->capacity-2;i++)
        {
            deque->massive_static_deque[i] = deque->massive_static_deque[i+1];
        }
        deque->massive_static_deque[deque->tail_index] = value;
    }
    else
    {
        deque->tail_index+=1;
        deque->massive_static_deque[deque->tail_index] = value;
    }
    return true;
}

int deque_static_peek_front(DequeStatic* deque)
{
    if (deque_static_is_empty(deque))
    {
        return -1;
    }
    return deque->massive_static_deque[deque->head_index];
}

int deque_static_peek_back(DequeStatic* deque)
{
    if (deque_static_is_empty(deque))
    {
        return -1;
    }
    return deque->massive_static_deque[deque->tail_index];
}

int deque_static_pop_front(DequeStatic* deque)
{
    if (deque_static_is_empty(deque))
    {
        return -1;
    }

    int value = deque->massive_static_deque[deque->head_index];

    if (deque->head_index == deque->tail_index)
    {
        deque->head_index = -1;
        deque->tail_index = -1;
        return value;
    }

    deque->head_index = (deque->head_index + 1) % deque->capacity;
    return value;
}

int deque_static_pop_back(DequeStatic* deque)
{
    if (deque_static_is_empty(deque))
    {
        return -1;
    }

    int value = deque->massive_static_deque[deque->tail_index];

    if (deque->head_index == deque->tail_index)
    {
        deque->head_index = -1;
        deque->tail_index = -1;
        return value;
    }

    deque->tail_index = (deque->tail_index - 1 + deque->capacity) % deque->capacity;
    return value;
}

int deque_static_search(DequeStatic *deque, int value)
{
    if (deque_static_is_empty(deque))
    {
        return -1;
    }
    int i = deque->head_index;
    while (1)
    {
        if(deque->massive_static_deque[i] == value)
        {
            return i;
        }
        if (i == deque->tail_index)
        {
            break;
        }
        i = (i + 1) % deque->capacity;
    }
    return -1;
}

#endif