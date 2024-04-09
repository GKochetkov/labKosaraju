#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <malloc.h>

#define STACK struct stack

STACK {
    int key;
    int value;
    STACK *next;
};

STACK* Create(int key, int value) {
    STACK *res;

    res = (STACK*)malloc(sizeof(STACK));
    res -> key = key;
    res -> value = value;
    res -> next = NULL;

    return res;
}

void Add(STACK *first, STACK *elem) {
    if (first -> next == NULL)
        first -> next = elem;
    else
        Add(first -> next, elem);
}

void Insert(STACK *pre, STACK *elem) {
    if (pre -> next == NULL) {
        pre -> next = elem;
        return;
    }

    if ((pre -> next -> value) < (elem -> value)) {
        elem -> next = pre -> next;
        pre -> next = elem;
        return;
    }
    else
        Insert(pre -> next, elem);
}

int Take(STACK *first) {
    STACK *elem = first -> next;
    int res = elem -> key;
    first -> next = elem -> next;
    free(elem);
    return res;
}

#endif // STACK_H_INCLUDED
