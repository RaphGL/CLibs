#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdio.h>

#define STACK_INIT(T)                              \
    typedef struct stack_##T                       \
    {                                              \
        struct stack_node_##T *head;               \
        int size;                                  \
        int max_size;                              \
    } Stack_##T;                                   \
                                                   \
    typedef struct stack_node_##T                  \
    {                                              \
        T item;                                    \
        struct stack_node_##T *next;               \
    } StackNode_##T;                               \
                                                   \
    Stack_##T *stack_new_##T(int size)             \
    {                                              \
        Stack_##T *new = malloc(sizeof(*new));     \
        new->max_size = size;                      \
        new->size = 0;                             \
        new->head = NULL;                          \
        return new;                                \
    }                                              \
                                                   \
    StackNode_##T *stack_node_##T(T val)           \
    {                                              \
        StackNode_##T *new = malloc(sizeof(*new)); \
        new->item = val;                           \
        new->next = NULL;                          \
        return new;                                \
    }                                              \
                                                   \
    void stack_push_##T(Stack_##T *s, T val)       \
    {                                              \
        StackNode_##T *new = stack_node_##T(val);  \
        StackNode_##T *tmp = s->head;              \
        new->next = tmp;                           \
        s->head = new;                             \
        s->size++;                                 \
    }                                              \
                                                   \
    T stack_pop_##T(Stack_##T *s)                      \
    {                                              \
        StackNode_##T *tmp = s->head;              \
        s->head = s->head->next;                   \
        T val = tmp->item;                         \
        free(tmp);                                 \
        s->size--;                                 \
        return val;                                \
    }                                              \
                                                   \
    void stack_free_##T(Stack_##T *s)              \
    {                                              \
        for (int i = 0; i < s->size; i++)          \
        {                                          \
            stack_pop_##T(s);                          \
        }                                          \
        free(s->head);                             \
        free(s);                                   \
    }
#endif