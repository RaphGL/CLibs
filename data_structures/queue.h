#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>

#define QUEUE_INIT(T)                                        \
    typedef struct queue_node_##T                            \
    {                                                        \
        T item;                                              \
        struct queue_node_##T *next;                         \
    } QueueNode_##T;                                         \
                                                             \
    typedef struct queue_##T                                 \
    {                                                        \
        int size;                                            \
        int max_size;                                        \
        QueueNode_##T *head;                                 \
    } Queue_##T;                                             \
                                                             \
    Queue_##T *queue_new_##T(int size)                       \
    {                                                        \
        Queue_##T *new = malloc(sizeof(*new));               \
        new->size = 0;                                       \
        new->max_size = size;                                \
        return new;                                          \
    }                                                        \
                                                             \
    void *queue_node_##T(T val)                              \
    {                                                        \
        QueueNode_##T *new = malloc(sizeof(*new));           \
        new->item = val;                                     \
        new->next = NULL;                                    \
    }                                                        \
                                                             \
    int queue_enqueue_##T(Queue_##T *q, T val)               \
    {                                                        \
        if (q->size <= q->max_size)                          \
        {                                                    \
            QueueNode_##T *new = queue_node_##T(val);        \
            new->next = q->head;                             \
            q->head = new;                                   \
            q->size++;                                       \
            return 0;                                        \
        }                                                    \
        return -1;                                           \
    }                                                        \
                                                             \
    int queue_dequeue_##T(Queue_##T *q)                      \
    {                                                        \
        if (q->size == 1)                                    \
        {                                                    \
            free(q->head);                                   \
            q->head = NULL;                                  \
            q->size--;                                       \
        }                                                    \
        if (q->size > 1)                                     \
        {                                                    \
            QueueNode_##T *tmp = q->head;                    \
            for (; tmp->next->next != NULL; tmp = tmp->next) \
                ;                                            \
            int val = tmp->next->item;                       \
            free(tmp->next);                                 \
            tmp->next = NULL;                                \
            q->size--;                                       \
            return val;                                      \
        }                                                    \
    }
#endif