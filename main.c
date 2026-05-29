#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

const char * input ="2*(123+42)-5";

int main(void){
	Lexer *l = initLexer(0, input);

	Token *tokens = tokenize(l);

	int i =0;
	Token *token = &tokens[i];
	while(token->type!=EOI){
		if (token->type==NUMBER){
			printf("NUMBER(%d)\n", token->value);
		}
		else {
			printf("%s\n", get_token_name(token));
		}
		i++;
		token = &tokens[i];
	}
	free(l);
	free(tokens);
	return 0;
}
