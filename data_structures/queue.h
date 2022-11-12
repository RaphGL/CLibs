#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>

#define QUEUE_INIT(T)                                  \
  /*Queue node*/                                       \
  typedef struct queue_node_##T                        \
  {                                                    \
    T item;                                            \
    struct queue_node_##T *next;                       \
  } QueueNode_##T;                                     \
                                                       \
  /*Queue wrapper structure*/                          \
  typedef struct queue_##T                             \
  {                                                    \
    int size;                                          \
    int max_size;                                      \
    QueueNode_##T *head;                               \
  } Queue_##T;                                         \
                                                       \
  /*Creates a new queue of size `size`*/               \
  Queue_##T *queue_new_##T(int size)                   \
  {                                                    \
    Queue_##T *new = malloc(sizeof(*new));             \
    new->size = 0;                                     \
    new->max_size = size;                              \
    return new;                                        \
  }                                                    \
                                                       \
  /*Allocates memory for a new queue node*/            \
  QueueNode_##T *queue_node_##T(T val)                 \
  {                                                    \
    QueueNode_##T *new = malloc(sizeof(*new));         \
    new->item = val;                                   \
    new->next = NULL;                                  \
    return new;                                        \
  }                                                    \
                                                       \
  /*Adds a new node to the queue*/                     \
  int queue_enqueue_##T(Queue_##T *q, T val)           \
  {                                                    \
    if (q->size < q->max_size || q->max_size == -1)       \
    {                                                  \
      QueueNode_##T *new = queue_node_##T(val);        \
      new->next = q->head;                             \
      q->head = new;                                   \
      q->size++;                                       \
      return 0;                                        \
    }                                                  \
    return -1;                                         \
  }                                                    \
                                                       \
  /*Removes a node from the queue*/                    \
  T queue_dequeue_##T(Queue_##T *q)                    \
  {                                                    \
    if (q->size > 1)                                   \
    {                                                  \
      QueueNode_##T *tmp = q->head;                    \
      for (; tmp->next->next != NULL; tmp = tmp->next) \
        ;                                              \
      T val = tmp->next->item;                         \
      free(tmp->next);                                 \
      tmp->next = NULL;                                \
      q->size--;                                       \
      return val;                                      \
    }                                                  \
    /* q->size == 1 */                                 \
    T val = q->head->item;                             \
    free(q->head);                                     \
    q->head = NULL;                                    \
    q->size--;                                         \
    return val;                                        \
  }                                                    \
                                                       \
  /*Returns the size of the queue*/                    \
  int queue_size_##T(Queue_##T *q)                     \
  {                                                    \
    return q->size;                                    \
  }                                                    \
                                                       \
  /*Frees queue and all of its nodes from memory*/     \
  void queue_free_##T(Queue_##T *q)                    \
  {                                                    \
    int size = queue_size_##T(q);                      \
    for (int i = 0; i < size; i++)                     \
    {                                                  \
      queue_dequeue_##T(q);                            \
    }                                                  \
    free(q);                                           \
  }
#endif
