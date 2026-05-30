#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"

int main(void){
    printf("Right now this interpeter uses integer values only. Dont input floats and be careful of integer overflow.\n");

    while(1){

        char *input = malloc(sizeof(char)*128);
        if (input==NULL){
            fprintf(stderr, "Input memory not allocated properly");
            return 1;
        }

        printf("mathint> ");
        fgets(input, 128, stdin);

        Lexer *l = initLexer(input);
        Tokens *tokens = tokenize(l);

        print_tokens(tokens);

        free(l);
        free(tokens->array);
        free(tokens);
        free(input);
    }
	return 0;
}
