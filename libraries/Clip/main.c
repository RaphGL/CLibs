#include <stdio.h>
#include "parse.h"

int main(int argc, char *argv[]) {
  clip_Token tokens[CLIP_TOKENSIZ];

  int ntok = clip_lex(tokens, argc, argv);

  if (ntok <= 0) {
    return 0;
  }

  clip_Op ptokens[CLIP_TOKENSIZ];
  ntok = clip_parse(ptokens, tokens, ntok);

  for (int i = 0; i < ntok; i++) {
    printf("%s ", ptokens[i].name);
    for (int j = 0; j < CLIP_ARGSIZ; j++) {
      if (ptokens[i].args[j])
        printf("  %s", ptokens[i].args[j]);
    }
    puts("");
  }

  clip_parse_free(ptokens);
  return 0;
}
