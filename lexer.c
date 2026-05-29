#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"

Token_Type set_literal_token_type(char c){
	if (c=='+'){
		return PLUS;
	}
	if (c=='-'){
		return MINUS;
	}
	if (c=='*'){
		return STAR;
	}
	if (c=='/'){
		return SLASH;
	}
	if (c=='('){
		return OPAREN;
	}
	if (c==')'){
		return CPAREN;
	}
	else{
		return UNKNOWN;
	}
}

// lexer constructor
Lexer *initLexer(int cursor, const char* str){
	Lexer *l = malloc(sizeof(Lexer));
	l->cursor = cursor;
	l->content = str;

	return l;	
}

char* get_token_name(Token *token){
	switch(token->type){
		case NUMBER:
			return "NUMBER";
		case PLUS:
			return "PLUS";
		case MINUS:
			return "MINUS";
		case STAR:
			return "STAR";
		case SLASH:
			return "SLASH";
		case OPAREN:
			return "OPAREN";
		case CPAREN:
			return "CPAREN";
		default:
			  return "UNKNOWN";
	}
}

Token *tokenize(Lexer *l){ //returning an array of tokens from a string

	// allocating memory for a Token table, str lenght will be always
	// longer than/same as count of tokens
	Token* tokens = malloc(sizeof(Token)*(strlen(l->content)+1));
	Token token;

	int token_count = 0;

	// looping through str untill the end
	while (l->content[l->cursor]!='\0'){
		// logic for NUMBER tokens
		if (isdigit(l->content[l->cursor])){
			int	digit_start = l->cursor;
			// calculating current digit with ASCII
			int digit = l->content[l->cursor] - '0';
			int integer = digit;
			int digit_count = 0;

			// loop that builds an integer 
			for (int i = 0; isdigit(l->content[l->cursor + 1 + i]); i++){
				digit = l->content[l->cursor + 1 + i] - '0';
				integer = integer*10 + digit;
				digit_count++;
			}

			// setting token attributes	
			token.type = NUMBER;
			token.value = integer;
			// setting cursor to position after integer
			l->cursor = digit_start+digit_count;
		}
		// literal token case (math operators eg. +,-,*,/,(,) )
		else {
			token.type = set_literal_token_type(l->content[l->cursor]);
		}
		// adding token to array
		tokens[token_count] = token;
		token_count++;
		l->cursor++;
	}
	token.type=EOI;
	tokens[token_count] = token;

	return tokens;
}

