#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"

Token_Type set_literal_token_type(char c){
    switch (c){
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return STAR;
        case '/': return SLASH;
        case '(': return OPAREN;
        case ')': return CPAREN;
        default: return UNKNOWN;
    }
}

// lexer constructor
Lexer *initLexer(int cursor, const char* str){
	Lexer *l = malloc(sizeof(Lexer));
    if (l==NULL){exit(1);}
	l->cursor = cursor;
	l->content = str;

	return l;	
}
void lexer_eat(Lexer *l){
    l->cursor++;
}

char* get_token_name(Token *token){
	switch(token->type){
		case NUMBER: return "NUMBER";
		case PLUS: return "PLUS";
		case MINUS: return "MINUS";
		case STAR: return "STAR";
		case SLASH: return "SLASH";
		case OPAREN: return "OPAREN";
		case CPAREN: return "CPAREN";
		default: return "UNKNOWN";
	}
}

Token *tokenize(Lexer *l){ //returning an array of tokens from a string

	// allocating memory for a Token table, str lenght will be always
	// longer than/same as count of tokens
	Token* tokens = malloc(sizeof(Token)*(strlen(l->content)+1));
    if (tokens==NULL) {exit(1);}
	Token token;

	int token_count = 0;

	// looping through str untill the end
	while (l->content[l->cursor]!='\0'){
        //skipping space
        if (isspace(l->content[l->cursor])){
            lexer_eat(l);
            continue;
        }
		// logic for NUMBER tokens
        else if (isdigit(l->content[l->cursor])){
			int integer = 0;
            while(isdigit(l->content[l->cursor])){
                integer = integer*10 +l->content[l->cursor] - '0';
                lexer_eat(l);
            }

			// setting token attributes	
			token.type = NUMBER;
			token.value = integer;
		}
		// literal token case (math operators eg. +,-,*,/,(,) )
        else {
			token.type = set_literal_token_type(l->content[l->cursor]);
            lexer_eat(l);
		}
		// adding token to array
		tokens[token_count] = token;
		token_count++;
	}
	token.type=EOI;
	tokens[token_count] = token;

	return tokens;
}

