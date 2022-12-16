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

// Prints the vector with the specified format specifier
void vec_printf(const char *restrict fmt, const vec_Vector *vec)
{
  printf("[");
  for (size_t i = 0; i < vec_len(vec); i++)
  {
    printf(" ");
    printf(fmt, vec->vec[i]);
  }
  printf(" ]\n");
}

// Inserts a new item at index
bool vec_insert(vec_Vector *vec, const size_t index, void *item)
{
  size_t len = vec->len - 1; // length before growing
  if (index > len)
  {
    return false;
  }

  vec_push(vec, vec->vec[len]);
  for (size_t i = vec->len; i > index; i--)
  {
    vec->vec[i] = vec->vec[i - 1];
  }

  vec->vec[index] = item;
  return true;
}

// Removes an item at index
bool vec_remove(vec_Vector *restrict vec, const size_t index)
{
  size_t len = vec->len - 1;
  if (index > len)
  {
    return false;
  }

  for (size_t i = index; i < vec->len; i++)
  {
    if (i + 1 < vec->len)
    {

      vec->vec[i] = vec->vec[i + 1];
    }
  }
  vec_pop(vec);

  return true;
}

bool vec_is_empty(const vec_Vector *vec)
{
  if (vec->len == 0 || vec->capacity == 0 || !vec->vec)
  {
    return true;
  }
  return false;
}

// Appends vector from src to dest
bool vec_append(vec_Vector *restrict dest, const vec_Vector *src)
{
  for (size_t i = 0; i < src->len; i++)
  {
    if (!vec_push(dest, src->vec[i]))
    {
      return false;
    }
  }
  return true;
}