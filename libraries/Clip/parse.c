#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

// copies lexed values into toks
// returns the number of tokens found
int clip_lex(clip_Token *toks, int argc, char *argv[]) {
  clip_Token tokens[CLIP_TOKENSIZ];
  int ntok = 0; // token occurrence used to index tokens[]
  for (int i = 1; i < argc; i++) {
    // make args beginning with -- long
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      tokens[ntok] = (clip_Token){
          .token = argv[i],
          .type = clip_LONG_FLAG,
      };
      // make args beginning with - short
    } else if (argv[i][0] == '-') {
      tokens[ntok] = (clip_Token){
          .token = argv[i],
          .type = clip_SHORT_FLAG,
      };
      // make args with no - arg types
    } else {
      tokens[ntok] = (clip_Token){
          .token = argv[i],
          .type = clip_ARG,
      };
    }
    ntok++;
  }

  memset(toks, 0, sizeof(*toks) * CLIP_TOKENSIZ);
  memcpy(toks, tokens, sizeof(clip_Token) * ntok);
  return ntok;
}

// allocates memory
// copies parsed values into ptokens
// returns size of ptokens
int clip_parse(clip_Op *ptokens, clip_Token *tokens, int ntok) {
  clip_Op parse_toks[CLIP_TOKENSIZ];
  clip_Op op;

  int curr_arg = 0;
  int curr_ptok = 0;
  for (int i = 0; i < ntok; i++) {
    switch (tokens[i].type) {
    case clip_SHORT_FLAG:
      op = (clip_Op){
          .type = clip_SHORT_FLAG,
          .name = tokens[i].token,
          .args = malloc(sizeof(op.args) * CLIP_ARGSIZ),
      };
      break;

    case clip_LONG_FLAG:
      op = (clip_Op){
          .type = clip_LONG_FLAG,
          .name = tokens[i].token,
          .args = malloc(sizeof(op.args) * CLIP_ARGSIZ),
      };
      break;

    case clip_ARG:
      op.args[curr_arg] = tokens[i].token;
      curr_arg++;
      // keeps appending args as long as its this arg type
      // otherwise a new token is allocated
      continue;
      break;
    }

    parse_toks[curr_ptok] = op;
    curr_ptok++;
  }

  memset(ptokens, 0, sizeof(*ptokens) * CLIP_TOKENSIZ);
  memcpy(ptokens, parse_toks, sizeof(clip_Op) * curr_ptok);
  return curr_ptok;
}

void clip_parse_free(clip_Op *ptokens) {
  for (int i = 0; i < CLIP_TOKENSIZ; i++) {
    if (ptokens[i].args) {
      free(ptokens[i].args);
    }
  }
}
