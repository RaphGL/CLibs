#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_INIT(T)                                                        \
  typedef struct                                                           \
  {                                                                        \
    /*The vector itself*/                                                  \
    T *vec;                                                                \
    /*Numbers of elements in the vector*/                                  \
    size_t size;                                                           \
    /* Amount of allocated memory in bytes*/                               \
    size_t capacity;                                                       \
  } vec_Vector_##T;                                                        \
                                                                           \
  /* Initializes an empty vector*/                                         \
  vec_Vector_##T vec_init_##T(void)                                        \
  {                                                                        \
    vec_Vector_##T vec = (vec_Vector_##T){                                 \
        .size = 0,                                                         \
        .vec = NULL,                                                       \
        .capacity = 0,                                                     \
    };                                                                     \
    return vec;                                                            \
  }                                                                        \
                                                                           \
  /* Inserts a new value into the vector*/                                 \
  vec_Vector_##T *vec_push_##T(vec_Vector_##T *vec, T val)                 \
  {                                                                        \
    /*allocates memory in this order*/                                     \
    /* 1 2 4 8 16 34*/                                                     \
    if (vec->capacity == 0)                                                \
    {                                                                      \
      vec->capacity = sizeof(val);                                         \
      vec->vec = malloc(sizeof(val));                                      \
      if (!vec->vec)                                                       \
      {                                                                    \
        return NULL;                                                       \
      }                                                                    \
    }                                                                      \
    else if ((vec->size * sizeof(val) + sizeof(val)) > vec->capacity)      \
    {                                                                      \
      vec->capacity *= 2;                                                  \
      T *tmp = realloc(vec->vec, vec->capacity);                           \
      if (!tmp)                                                            \
      {                                                                    \
        return NULL;                                                       \
      }                                                                    \
      vec->vec = tmp;                                                      \
    }                                                                      \
                                                                           \
    vec->vec[vec->size] = val;                                             \
    vec->size++;                                                           \
    return vec;                                                            \
  }                                                                        \
                                                                           \
  /* Removes the last element from vector*/                                \
  T vec_pop_##T(vec_Vector_##T *vec)                                       \
  {                                                                        \
    T val = vec->vec[--vec->size];                                         \
    vec->size--;                                                           \
    return val;                                                            \
  }                                                                        \
                                                                           \
  /*Frees the whole vector from memory*/                                   \
  void vec_free_##T(vec_Vector_##T *vec) { free(vec->vec); }               \
                                                                           \
  /*Prints the vector structure*/                                          \
  void vec_print_##T(vec_Vector_##T *vec)                                  \
  {                                                                        \
    printf("[ ");                                                          \
    for (size_t i = 0; i < vec->size; i++)                                 \
    {                                                                      \
      printf("%d ", vec->vec[i]);                                          \
    }                                                                      \
    printf("]\n");                                                         \
  }                                                                        \
                                                                           \
  /* Removes an element from vector at index*/                             \
  T vec_remove_##T(vec_Vector_##T *vec, size_t index)                      \
  {                                                                        \
    if (index > vec->size)                                                 \
    {                                                                      \
      return -1;                                                           \
    }                                                                      \
                                                                           \
    T val = vec->vec[index];                                               \
    for (size_t i = index; i <= vec->size; i++)                            \
    {                                                                      \
      vec->vec[i] = vec->vec[i + 1];                                       \
    }                                                                      \
    vec->size--;                                                           \
    return val;                                                            \
  }                                                                        \
                                                                           \
  /* Inserts an element to vector on index*/                               \
  vec_Vector_##T *vec_insert_##T(vec_Vector_##T *vec, size_t index, T val) \
  {                                                                        \
    if (index > vec->size)                                                 \
    {                                                                      \
      return NULL;                                                         \
    }                                                                      \
                                                                           \
    vec_push_##T(vec, val);                                                \
    for (size_t i = vec->size; i > index; i--)                             \
    {                                                                      \
      vec->vec[i] = vec->vec[i - 1];                                       \
    }                                                                      \
    vec->vec[index] = val;                                                 \
                                                                           \
    return vec;                                                            \
  }                                                                        \
                                                                           \
  /* Amount of memory being used by the vector in bytes*/                  \
  int vec_capacity_##T(vec_Vector_##T *vec) { return vec->capacity; }      \
                                                                           \
  /* Amount of elements in the vector*/                                    \
  int vec_size_##T(vec_Vector_##T *vec) { return vec->size; }              \
                                                                           \
  /* Return an element from vector at index*/                              \
  T vec_get_##T(vec_Vector_##T *vec, size_t index)                         \
  {                                                                        \
    if (index > vec->size)                                                 \
    {                                                                      \
      return -1;                                                           \
    }                                                                      \
                                                                           \
    return vec->vec[index];                                                \
  }                                                                        \
                                                                           \
  /* Returns true if vector is empty*/                                     \
  bool vec_is_empty_##T(vec_Vector_##T *vec)                               \
  {                                                                        \
    if (vec->size == 0)                                                    \
    {                                                                      \
      return true;                                                         \
    }                                                                      \
    else                                                                   \
    {                                                                      \
      return false;                                                        \
    }                                                                      \
  }
#endif
