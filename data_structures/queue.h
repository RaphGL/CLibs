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
    QueueNode_##T *queue_node_##T(T val)                     \
    {                                                        \
        QueueNode_##T *new = malloc(sizeof(*new));           \
        new->item = val;                                     \
        new->next = NULL;                                    \
        return new;                                          \
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
    T queue_dequeue_##T(Queue_##T *q)                        \
    {                                                        \
        if (q->size > 1)                                     \
        {                                                    \
            QueueNode_##T *tmp = q->head;                    \
            for (; tmp->next->next != NULL; tmp = tmp->next) \
                ;                                            \
            T val = tmp->next->item;                         \
            free(tmp->next);                                 \
            tmp->next = NULL;                                \
            q->size--;                                       \
            return val;                                      \
        }                                                    \
        /* q->size == 1 */                                   \
        T val = q->head->item;                               \
        free(q->head);                                       \
        q->head = NULL;                                      \
        q->size--;                                           \
        return val;                                          \
    }                                                        \
                                                             \
    int queue_size_##T(Queue_##T *q)                         \
    {                                                        \
        QueueNode_##T *tmp = q->head;                        \
        int size = 0;                                        \
        for (; tmp != NULL; tmp = tmp->next)                 \
        {                                                    \
            size++;                                          \
        }                                                    \
        return size;                                         \
    }                                                        \
                                                             \
    void queue_free_##T(Queue_##T *q)                        \
    {                                                        \
        int size = queue_size_##T(q);                        \
        for (int i = 0; i < size; i++)                       \
        {                                                    \
            queue_dequeue_##T(q);                            \
        }                                                    \
        free(q);                                             \
    }
#endif