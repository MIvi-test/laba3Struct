#ifndef DYNAMIC_DEQUE_C
#define DYNAMIC_DEQUE_C

#include "deque.h"


DequeDynamic deque_dynamic_init(DequeDynamic *interface)
{
    DequeDynamic init = {NULL, NULL, -1};

    if (interface->id != 0)
    {
        DequeDynamic *copy = interface;
        // goto right;
        while (copy->front != NULL)
        {
            copy = copy->front;
        }
        init.front = copy;
        // goto right;
        copy = interface;
        while (copy->back != NULL)
        {
            copy = copy->back;
        }
        init.back = copy;
    }
    else
    {
        DequeDynamic *head = (DequeDynamic *)malloc(sizeof(DequeDynamic));
        if (!head)
        {
            return init;
        }
        DequeDynamic *tail = (DequeDynamic *)malloc(sizeof(DequeDynamic));
        if (!tail)
        {
            return init;
        }

        interface->back = head;
        interface->front= tail;
        head->front = tail;
        head->back = NULL;
        head->id = 0;
        tail->back = head;
        tail->front = NULL;
        tail->id = 0;
        init.back = head;
        init.front = tail;
    }
    return init;
}

bool deque_dynamic_is_empty(DequeDynamic *interface)
{
    if(interface->back->id == 0 && interface->front->id == 0)
    {
        return 0;
    }
    return 1;
}

bool deque_dynamic_push_front(DequeDynamic *interface, int value)
{
    if (interface == NULL)
    {
        return false;
    }
    DequeDynamic *new = (DequeDynamic*)malloc(sizeof(DequeDynamic));
    if(!new)
    {
        return false;
    }
    new->id = value;
    DequeDynamic *copy = interface;
    while(copy->front != NULL)
    {
        copy = copy->front;
    } 
    new->back = copy->back;
    new->front = copy;
    copy->back->front = new;
    copy->back = new;
    (*interface) = (*new);
    return true;
}

bool deque_dynamic_push_back(DequeDynamic *interface, int value)
{
    DequeDynamic *new = (DequeDynamic*)malloc(sizeof(DequeDynamic));
    if(!new)
    {
        return false;
    }
    new->id = value;
    DequeDynamic *copy = interface;
    while(copy->back != NULL)
    {
        copy = copy->back;
    } //дошли до head
    new->back = copy;
    new->front = copy->front;
    copy->front->back = new;
    copy->front = new;
    (*interface) = (*new);
    return true;
}

int deque_dynamic_peek_front(DequeDynamic *interface)
{
    if (deque_dynamic_is_empty(interface))
    {
        return -1;
    }
    DequeDynamic *copy = interface;
    while(copy->front == NULL)
    return copy->back->id;
}

int deque_dynamic_peek_back(DequeDynamic *interface)
{
    if (deque_dynamic_is_empty(interface))
    {
        return -1;
    }
    DequeDynamic *copy = interface;
    while(copy->front == NULL)
    return copy->back->id;
}

int deque_dynamic_pop_front(DequeDynamic *interface)
{
    if (deque_dynamic_is_empty(interface) || interface->front->id == 0)
    {
        return -1;
    }

    DequeDynamic *copy = interface;
    while(copy->front->id != 0)
    {
        copy = copy->front; 
    }
    //оставились на удаляемом объекте
    copy->back->front = copy->front;
    copy->front->back = copy->back;
    interface->front = copy->back->front;
    interface->back = copy->back->back;
    interface->id = copy->back->id;
    int value = copy->id;
    free(copy);
    return value;

}

int deque_dynamic_pop_back(DequeDynamic *interface)
{
    if (deque_dynamic_is_empty(interface) || interface->back->id == 0)
    {
        return -1;
    }

    DequeDynamic *copy = interface;
    while(copy->back->id != 0)
    {
        copy = copy->back; 
    }
    //оставились на удаляемом объекте
    copy->back->front = copy->front;
    copy->front->back = copy->back;
    int value = copy->id;
    free(copy);
    return value;
}

void deque_dynamic_destroy(DequeDynamic *interface)
{
    if(interface == NULL)
    {
        return;
    }
    DequeDynamic *start = interface->back;
    while(start->back != NULL)
    {
        start = start->back;
    }
    DequeDynamic *temp; 
    while(start != NULL)
    {
        temp = start->front;
        free(start);
        start = temp;
    }
    return;
}

DequeDynamic *deque_dynamic_search(DequeDynamic *interface, int search_value)
{
    if(interface == NULL || search_value <=0)
    {
        return NULL;   
    }

    DequeDynamic *cursor = interface->back;
    while(cursor->front != NULL)
    {
        if(cursor->id == search_value)
        {
            interface->back = cursor->back;
            interface->id = cursor->id;
            interface->front = cursor->front;
            return cursor;
        }
        cursor = cursor->front;
    }
    cursor = interface->front;
    while(cursor->back != NULL)
    {
        if(cursor->id == search_value)
        {
            interface->back = cursor->back;
            interface->id = cursor->id;
            interface->front = cursor->front;
            return cursor;
        }
        cursor = cursor->back;
    }
    return NULL;
}

#endif