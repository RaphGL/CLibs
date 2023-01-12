#define CLIP_TOKENSIZ 512
#define CLIP_ARGSIZ 24

typedef enum clip_token_type {
  clip_ARG,
  clip_SHORT_FLAG,
  clip_LONG_FLAG
} clip_TokenType;

typedef struct clip_token {
  clip_TokenType type;
  char *token;
} clip_Token;

typedef struct clip_op {
  clip_TokenType type;
  char *name;
  char **args; // stores argv pointers
} clip_Op;

// copies lexed values into toks 
// returns the number of tokens found
int clip_lex(clip_Token *toks, int argc, char *argv[]);

// allocates memory
// copies parsed values into ptokens
// returns size of ptokens
int clip_parse(clip_Op *ptokens, clip_Token *tokens, int ntok);

void clip_parse_free(clip_Op *ptokens);
