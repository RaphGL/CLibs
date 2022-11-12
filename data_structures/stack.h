#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT(T)                                                \
  /*Wrapper around stack structure*/                                 \
  typedef struct stack_##T                                           \
  {                                                                  \
    struct stack_node_##T *head;                                     \
    int size;                                                        \
  } Stack_##T;                                                       \
                                                                     \
  /*Stack node structure*/                                           \
  typedef struct stack_node_##T                                      \
  {                                                                  \
    T item;                                                          \
    struct stack_node_##T *next;                                     \
  } StackNode_##T;                                                   \
                                                                     \
  /*Create a new stack*/                                             \
  Stack_##T *stack_new_##T()                                         \
  {                                                                  \
    Stack_##T *new = malloc(sizeof(*new));                           \
    if (!new)                                                        \
    {                                                                \
      return NULL;                                                   \
    }                                                                \
    new->size = 0;                                                   \
    new->head = NULL;                                                \
    return new;                                                      \
  }                                                                  \
                                                                     \
  /*Allocates memory for a new stack node and assigns values to it*/ \
  StackNode_##T *stack_node_##T(T val)                               \
  {                                                                  \
    StackNode_##T *new = malloc(sizeof(*new));                       \
    new->item = val;                                                 \
    new->next = NULL;                                                \
    return new;                                                      \
  }                                                                  \
                                                                     \
  /*Pushes a new value to the stack*/                                \
  int stack_push_##T(Stack_##T *s, T val)                            \
  {                                                                  \
    StackNode_##T *new = stack_node_##T(val);                        \
    if (!new)                                                        \
    {                                                                \
      return -1;                                                     \
    }                                                                \
    StackNode_##T *tmp = s->head;                                    \
    new->next = tmp;                                                 \
    s->head = new;                                                   \
    s->size++;                                                       \
    return 0;                                                        \
  }                                                                  \
                                                                     \
  /*Pops a value from the stack and frees it from memory*/           \
  T stack_pop_##T(Stack_##T *s)                                      \
  {                                                                  \
    StackNode_##T *tmp = s->head;                                    \
    s->head = s->head->next;                                         \
    T val = tmp->item;                                               \
    free(tmp);                                                       \
    s->size--;                                                       \
    return val;                                                      \
  }                                                                  \
                                                                     \
  /*Deallocates the stack and all of its nodes from memory*/         \
  void stack_free_##T(Stack_##T *s)                                  \
  {                                                                  \
    for (int i = 0; i < s->size; i++)                                \
    {                                                                \
      stack_pop_##T(s);                                              \
    }                                                                \
    free(s->head);                                                   \
    free(s);                                                         \
  }                                                                  \
                                                                     \
  /*Returns the size of the stack*/                                  \
  int stack_size_##T(Stack_##T *s)                                   \
  {                                                                  \
    return s->size;                                                  \
  }
#endif
