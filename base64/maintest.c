#include "base64.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const char *decodee = "light w";
  char *encoded = (char *)base64_encode((uint8_t *)decodee, strlen(decodee));
  char *decoded = (char *)base64_decode(encoded, strlen(encoded));
  assert(strcmp(decodee, decoded) == 0);

  free((void *)encoded);
  free((void *)decoded);

  // -------

  encoded = (char *)base64_encode((uint8_t *)"Man", 3);
  assert(strcmp(encoded, "TWFu") == 0);
  decoded = (char *)base64_decode(encoded, strlen(encoded));
  assert(strcmp(decoded, "Man") == 0);
  free((void *)encoded);
  free((void *)decoded);

  // ------

  encoded = (char *)base64_encode((uint8_t *)"light work.", 11);
  assert(strcmp(encoded, "bGlnaHQgd29yay4=") == 0);
  decoded = (char *)base64_decode(encoded, strlen(encoded));
  assert(strcmp(decoded, "light work.") == 0);
  free((void *)encoded);
  free((void *)decoded);

  // ------

  // todo: still crashing atm as function fails for args with len < 3
  // encoded = (char *)base64_encode((uint8_t *)"ma", 2);
  // assert(strcmp(encoded, "TWE=") == 0);
  // decoded = (char *)base64_decode(encoded, strlen(encoded));
  // assert(strcmp(decoded, "TWE=") == 0);
  // free((void *)encoded);
  // free((void *)decoded);

  puts("tests passed.");
  return 0;
}
