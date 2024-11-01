#include "base64.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const char *decodee = "this is some long sentence to be encoded in base64.";
  char *encoded = (char *)base64_encode((uint8_t *)decodee, strlen(decodee));
  char *decoded = (char *)base64_decode(encoded, strlen(encoded));
  assert(strcmp(decodee, decoded) == 0);

  free((void *)encoded);
  free((void *)decoded);

  // ------

  struct {
    char *encoded;
    char *decoded;
  } res[] = {
      {.decoded = "Man", .encoded = "TWFu"},
      {.decoded = "light work.", .encoded = "bGlnaHQgd29yay4="},
      {.decoded = "ma", .encoded = "bWE="},
  };

  for (size_t i = 0; i < sizeof(res) / sizeof(res[0]); i++) {
    encoded = (char *)base64_encode((uint8_t *)res[i].decoded,
                                    strlen(res[i].decoded));
    assert(strcmp(encoded, res[i].encoded) == 0);
    decoded = (char *)base64_decode(encoded, strlen(encoded));
    assert(strcmp(decoded, res[i].decoded) == 0);

    free(encoded);
    free(decoded);
  }

  puts("tests passed.");
  return 0;
}
