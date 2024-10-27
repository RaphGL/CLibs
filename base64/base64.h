#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

const char *const base64_encode(const uint8_t *const data, size_t data_size);
const char *base64_decode(const char *base64_str, size_t base64_len);

#endif
