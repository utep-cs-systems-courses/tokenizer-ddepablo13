#include <stdio.h>
#include "tokenizer.h"
#include "history.h"
#include <stdlib.h>
  //implement strlen
  size_t my_strlen(const char *str){
    size_t len = 0;
    while(*str != '\0'){
      len++;
      str++;
    }
    return len;
  }

  //implement strcmp
  int my_strcmp(const char *str1, const char *str2){
    while(*str1 != '\0' && *str2 != '\0'){
      if(*str1 != *str2){
	return *str1 - *str2;
      }
      str1++;
      str2++;
    }
    return *str1 - *str2;
  }

  void print_help(){
    printf("Available commands:\n");
    printf("   quit   - Exits program\n");
    printf("   !<num>   - Recall a command from history by its number\n");
    printf("   Any other string   - Tokenize the string and add it to history\n");
}

  int main(){
    List *history = init_history();
    printf("Initialized history.\n");

    char input[100];

    print_help();

  start_loop:

    printf("> ");
    fgets(input, 100, stdin);
    input[my_strlen(input) - 1] = '\0';

    if (my_strcmp(input, "quit") == 0) {
      printf("Exiting..\n");
      goto end_program;
    } //History recall commands like !1 !2.
    else if (input[0] == '!') {
      int id = atoi(input + 1);
      char *str = get_history(history, id);
      if (str) {
	printf("Tokenizing string from history: %s\n", str);
	char **tokens = tokenize(str);
	print_tokens(tokens);
	free_tokens(tokens);
      } else {
	printf("No such history item. Type valid number like '!1'\n");
      }
      goto start_loop;
    } else {
      printf("Adding to history and tokenizing it.\n", input);
      add_history(history, input);

      char **tokens = tokenize(input);
      print_tokens(tokens);
      free_tokens(tokens);
      goto start_loop;
    }
  end_program:

    printf("Freeing history.\n");
    free_history(history);

    return 0;
    
  }
