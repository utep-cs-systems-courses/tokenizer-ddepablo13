#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

int space_char(char c){
  return (c == ' '|| c == '\t');
}

int non_space_char(char c){
  return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *s){
  while (space_char(*s)) s++;
  return (*s == '\0') ? NULL : s;
}

char *token_terminator(char *token){
  while (non_space_char(*token)) token++;
  return token;
}

int count_tokens(char *s){
  int count = 0;
  while ((s = token_start(s)) != NULL){
    s = token_terminator(s);
    count++;
  }
  return count;
}

char *copy_str(char *inStr, short len){
  char *outStr = malloc(len + 1);
  for(int i = 0; i < len; i++){
    outStr[i] = inStr[i];
  }
  outStr[len] = '\0';
  return outStr;
}

char **tokenize(char *s){
  int token_count = count_tokens(s);
  char **tokens = malloc((token_count + 1) * sizeof(char *));
  char *start, *end;
  for (int i = 0; i < token_count; i++){
    start = token_start(s);
    end = token_terminator(start);
    tokens[i] = copy_str(start, end - start);
    s = end;
  }
  tokens[token_count] = NULL;
  return tokens;
}

void print_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    printf("Token %d: %s\n", i, tokens[i]);
  }
}

void free_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }
  free(tokens);
}
