#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec_vector
{
  size_t len;
  size_t capacity;
  void **vec;
} vec_Vector;

// Initializes a new vector
vec_Vector *vec_new(void)
{
  vec_Vector *new = malloc(sizeof(vec_Vector));
  new->capacity = 0;
  new->len = 0;
  new->vec = NULL;
  return new;
}

// Pushes a value to vector
bool vec_push(vec_Vector *restrict vec, void *item)
{
  // initialize vector if needed
  if (!vec->vec)
  {
    vec->vec = malloc(sizeof(void *));
    if (!vec->vec)
    {
      return false;
    }
    vec->capacity = sizeof(void *);
    vec->len = 1;
    vec->vec[0] = item;
    return true;
  }

  // grow vector if needed
  if (vec->len * sizeof(void *) + sizeof(void *) > vec->capacity)
  {
    void *tmp = realloc(vec->vec, vec->capacity * 2);
    if (!tmp)
    {
      return false;
    }
    vec->vec = tmp;
    vec->capacity *= 2;
  }

  vec->vec[vec->len] = item;
  vec->len++;
  return true;
}

// Removes an item from the end of the vector and assigns it to dest
void *vec_pop(vec_Vector *restrict vec)
{
  if (!vec->vec || vec->len <= 0 || vec->capacity == 0)
  {
    return NULL;
  }

  vec->len--;
  return &vec->vec[vec->len];
}

// Returns how many items are in the vector
size_t vec_len(const vec_Vector *vec) { return vec->len; }

// Returns the total amount of items that can currently be stored
size_t vec_capacity(const vec_Vector *vec) { return vec->capacity; }

// Clears out all the memory used by the vector
void vec_free(vec_Vector *restrict vec)
{
  if (!vec->vec)
  {
    return;
  }

  free(vec->vec);
  free(vec);
}

// Returns item at index
void *vec_get(const vec_Vector *vec, const size_t index)
{
  if (!vec->vec || index >= vec->len || vec->capacity == 0)
  {
    return NULL;
  }

  return &vec->vec[index];
}