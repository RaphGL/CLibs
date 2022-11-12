#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // The vector itself
  int *vec;
  // Numbers of elements in the vector
  size_t size;
  // Amount of allocated memory in bytes
  size_t capacity;
} vec_Vector;

/*
 * Initializes an empty vector
 *
 * @return vec_Vector type
 */
vec_Vector vec_init(void) {
  vec_Vector vec = (vec_Vector){
      .size = 0,
      .vec = NULL,
      .capacity = 0,
  };
  return vec;
}

/*
 * Inserts a new value into the vector
 *
 * @param vec Initialized vector
 * @param val Value to be pushed
 *
 * @return NULL if an error occurred
 */
vec_Vector *vec_push(vec_Vector *vec, int val) {
  // allocates memory in this order
  // 1 2 4 8 16 34
  if (vec->capacity == 0) {
    vec->capacity = sizeof(val);
    vec->vec = malloc(sizeof(val));
    if (!vec->vec) {
      return NULL;
    }
  } else if ((vec->size * sizeof(val) + sizeof(val)) > vec->capacity) {
    vec->capacity *= 2;
    int *tmp = realloc(vec->vec, vec->capacity);
    if (!tmp) {
      return NULL;
    }
    vec->vec = tmp;
  }

  vec->vec[vec->size] = val;
  vec->size++;
  return vec;
}

/*
 * Removes the last element from vector
 *
 * @param vec Initialized vector
 *
 * @return Popped value
 */
int vec_pop(vec_Vector *vec) {
  int val = vec->vec[vec->size];
  vec->size--;
  return val;
}

/*
 * Frees the whole vector from memory
 *
 * @param vec Initialized vector
 *
 * @return None
 */
void vec_free(vec_Vector *vec) { free(vec->vec); }

/*
 * Prints the vector structure
 *
 * @param vec Initialized vector
 *
 * @return None
 */
void vec_print(vec_Vector *vec) {
  printf("[ ");
  for (size_t i = 0; i < vec->size; i++) {
    printf("%d ", vec->vec[i]);
  }
  printf("]\n");
}

/*
 * Removes an element from vector at index
 *
 * @param vec Initialized vector
 * @param index Index of an element on vector
 *
 * @return -1 if index is invalid
 */
int vec_remove(vec_Vector *vec, size_t index) {
  if (index > vec->size) {
    return -1;
  }

  int val = vec->vec[index];
  for (size_t i = index; i <= vec->size; i++) {
    vec->vec[i] = vec->vec[i + 1];
  }
  vec->size--;
  return val;
}

/*
 * Inserts an element to vector on index
 *
 * @param vec Initialized vector
 * @param index Index of element in vector
 * @param val Value to be inserted
 *
 * @return NULL if index is invalid
 */
vec_Vector *vec_insert(vec_Vector *vec, size_t index, int val) {
  if (index > vec->size) {
    return NULL;
  }

  vec_push(vec, val);
  for (size_t i = vec->size; i > index; i--) {
    vec->vec[i] = vec->vec[i - 1];
  }
  vec->vec[index] = val;

  return vec;
}

/*
 * Amount of memory being used by the vector in bytes
 *
 * @param vec Initialized vector
 *
 * @return Capacity of the vector
 */
int vec_capacity(vec_Vector *vec) { return vec->capacity; }

/*
 * Amount of elements in the vector
 *
 * @param vec Initialized vector
 *
 * @return Size of the vector
 */
int vec_size(vec_Vector *vec) { return vec->size; }

/*
 * Return an element from vector at index
 *
 * @param vec Initialized vector
 * @param index Index of an element in vector
 */
int vec_get(vec_Vector *vec, size_t index) {
  if (index > vec->size) {
    return -1;
  }

  return vec->vec[index];
}

/*
 * Returns true if vector is empty
 *
 * @param vec Initialized vector
 *
 * @return True if vector is empty
 */
bool vec_is_empty(vec_Vector *vec) {
  if (vec->size == 0) {
    return true;
  } else {
    return false;
  }
}
#endif
