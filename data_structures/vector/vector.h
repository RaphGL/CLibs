#include <stddef.h>

typedef struct vec_vector vec_Vector;

// Initializes a new vector
vec_Vector vec_new(void);
// Pushes a value to vector
bool vec_push(vec_Vector *restrict vec, void *item);
// Removes an item from the end of the vector and assigns it to dest
void *vec_pop(vec_Vector *restrict vec);
// Returns how many items are in the vector
size_t vec_len(const vec_Vector *vec);
// Returns the total amount of items that can currently be stored
size_t vec_capacity(const vec_Vector *vec);
// Clears out all the memory used by the vector
void vec_free(vec_Vector *restrict vec);
// Returns item at index
void *vec_get(const vec_Vector *vec, const size_t index);