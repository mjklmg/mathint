#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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

void print_token(Token* token){
    if (token->type==NUMBER){
        printf("NUMBER(%d)\n", token->value);
    }
    else {
        printf("%s\n", get_token_name(token));
    }
}

void print_tokens(Tokens *tokens){
    int count = tokens->token_count;
    for (int i = 0; i<count ; i++){
        print_token(&tokens->array[i]);
    }
}

// lexer constructor
Lexer *initLexer(const char* input){
	Lexer *lexer = malloc(sizeof(Lexer));
    if (lexer==NULL){
        return lexer;
    }
	lexer->cursor = 0;
// passing input to the lexer
    char * content = malloc(strlen(input)+1);
	strcpy(content, input);
    lexer->content=content;

	return lexer;	
}

void lexer_eat(Lexer *lexer){
    lexer->cursor++;
}

Tokens *tokenize(Lexer *lexer){ //returning an array of tokens from a string

	// allocating memory for a Token table, str lenght will be always
	// longer than/same as count of tokens
	Token* array_of_tokens = malloc(sizeof(Token)*(strlen(lexer->content)));
    if (array_of_tokens == NULL){ 
        return NULL;
    }

	Token token;

	int token_count = 0;

	// looping through str untill the end
	while (lexer->content[lexer->cursor]!='\0'){
        //skipping space
        if (isspace(lexer->content[lexer->cursor])){
            lexer_eat(lexer);
            continue;
        }
		// logic for NUMBER tokens
        else if (isdigit(lexer->content[lexer->cursor])){
			int integer = 0;
            while(isdigit(lexer->content[lexer->cursor])){
                // building integer from chars converted to ints with ASCII
                integer = integer*10 + lexer->content[lexer->cursor] - '0';
                lexer_eat(lexer);
            }

			// setting token attributes	
			token.type = NUMBER;
			token.value = integer;
		}
		// literal token case (math operators eg. +,-,*,/,(,) )
        else {
			token.type = set_literal_token_type(lexer->content[lexer->cursor]);
            lexer_eat(lexer);
		}
		// adding token to array
		array_of_tokens[token_count] = token;
		token_count++;
	}
    // creating Tokens struct for returning both array_of_tokens and token_count
	Tokens *tokens = malloc(sizeof(Tokens));
    if (tokens==NULL) {
        return tokens;
    }
    tokens->array=array_of_tokens;
    tokens->token_count=token_count;

	return tokens;
}

