#include "base64.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const uint8_t base64_encode_map[] = {
    [0] = 'A',  [1] = 'B',  [2] = 'C',  [3] = 'D',  [4] = 'E',  [5] = 'F',
    [6] = 'G',  [7] = 'H',  [8] = 'I',  [9] = 'J',  [10] = 'K', [11] = 'L',
    [12] = 'M', [13] = 'N', [14] = 'O', [15] = 'P', [16] = 'Q', [17] = 'R',
    [18] = 'S', [19] = 'T', [20] = 'U', [21] = 'V', [22] = 'W', [23] = 'X',
    [24] = 'Y', [25] = 'Z', [26] = 'a', [27] = 'b', [28] = 'c', [29] = 'd',
    [30] = 'e', [31] = 'f', [32] = 'g', [33] = 'h', [34] = 'i', [35] = 'j',
    [36] = 'k', [37] = 'l', [38] = 'm', [39] = 'n', [40] = 'o', [41] = 'p',
    [42] = 'q', [43] = 'r', [44] = 's', [45] = 't', [46] = 'u', [47] = 'v',
    [48] = 'w', [49] = 'x', [50] = 'y', [51] = 'z', [52] = '0', [53] = '1',
    [54] = '2', [55] = '3', [56] = '4', [57] = '5', [58] = '6', [59] = '7',
    [60] = '8', [61] = '9', [62] = '+', [63] = '/',
    // `=` -> padding
};

static const uint8_t base64_decode_map[] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,
    ['G'] = 6,  ['H'] = 7,  ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11,
    ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15, ['Q'] = 16, ['R'] = 17,
    ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25, ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29,
    ['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35,
    ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39, ['o'] = 40, ['p'] = 41,
    ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47,
    ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53,
    ['2'] = 54, ['3'] = 55, ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59,
    ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63,
    // `=` -> padding
};

const char *const base64_encode(const uint8_t *const data, size_t data_size) {
  const size_t remaining = data_size % 3;
  const size_t base64_len =
      ((double)data_size * 8) / 6 + 4 /* maximum padding + null char */;
  char *result = malloc(base64_len);
  if (!result) {
    return NULL;
  }
  memset(result, 0, base64_len);

  size_t base64_idx = 0;
  for (size_t i = 0; i < data_size - remaining; i += 3) {
    uint8_t byte1 = data[i], byte2 = data[i + 1], byte3 = data[i + 2];

    uint8_t octet1 = (byte1 & 0b11111100) >> 2,
            octet2 = ((byte1 & 0b11) << 4) | ((byte2 & 0b11110000) >> 4),
            octet3 = ((byte2 & 0b1111) << 2) | ((byte3 & 0b11000000) >> 6),
            octet4 = (byte3 & 0b111111);

    result[base64_idx++] = base64_encode_map[octet1];
    result[base64_idx++] = base64_encode_map[octet2];
    result[base64_idx++] = base64_encode_map[octet3];
    result[base64_idx++] = base64_encode_map[octet4];
  }

  if (remaining == 1) {
    uint8_t byte1 = data[data_size - 1];
    uint8_t octet1 = (byte1 & 0b11111100) >> 2;
    uint8_t octet2 = (byte1 & 0b11) << 4;

    result[base64_idx++] = base64_encode_map[octet1];
    result[base64_idx++] = base64_encode_map[octet2];
    result[base64_idx++] = '=';
    result[base64_idx++] = '=';
  } else if (remaining == 2) {
    uint8_t byte1 = data[data_size - 2];
    uint8_t byte2 = data[data_size - 1];

    uint8_t octet1 = (byte1 & 0b11111100) >> 2;
    uint8_t octet2 = ((byte1 & 0b11) << 4) | ((byte2 & 0b11110000) >> 4);
    uint8_t octet3 = ((byte2 & 0b1111) << 2);

    result[base64_idx++] = base64_encode_map[octet1];
    result[base64_idx++] = base64_encode_map[octet2];
    result[base64_idx++] = base64_encode_map[octet3];
    result[base64_idx++] = '=';
  }

  return result;
}

const char *base64_decode(const char *base64_str, size_t base64_len) {
  size_t padding_len = 0;
  for (size_t i = base64_len - 1; base64_str[i] == '=' && i >= 0; i--) {
    ++padding_len;
  }
  const size_t result_len = ((base64_len - padding_len) * 6) / 8 + 1;
  char *result = malloc(result_len);
  if (!result) {
    return NULL;
  }
  memset(result, 0, result_len);

  size_t result_idx = 0;
  for (size_t i = 0; i < base64_len; i += 4) {
    uint8_t octet1 = base64_decode_map[base64_str[i]];
    uint8_t octet2 = base64_decode_map[base64_str[i + 1]];
    uint8_t octet3 = base64_decode_map[base64_str[i + 2]];
    uint8_t octet4 = base64_decode_map[base64_str[i + 3]];

    uint8_t byte1 = (octet1 << 2) | ((octet2 & 0b110000) >> 4),
            byte2 = (octet2 << 4) | ((octet3 & 0b111100) >> 2),
            byte3 = (octet3 << 6) | octet4;

    result[result_idx++] = byte1;
    result[result_idx++] = byte2;
    result[result_idx++] = byte3;
  }

  return result;
}
