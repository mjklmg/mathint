#ifndef LEXER_H

#define LEXER_H

#include <stddef.h>
typedef enum Token_Type {
	UNKNOWN = 0,
	NUMBER,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	OPAREN,
	CPAREN
} Token_Type ;

typedef struct Token {
	Token_Type type;
	int value;
} Token;

typedef struct Tokens {
    int token_count;
    Token * array;
} Tokens;

typedef struct Lexer {
	int cursor; // cursor position 0;n
	const char* content; // string thats currently tokenized
} Lexer;

void print_token(Token* token);

void print_tokens(Tokens *tokens);

Token_Type set_literal_token_type(char c);

char* get_token_name(Token *token);

Lexer *initLexer(const char* input);

void lexer_eat(Lexer *l);

Tokens *tokenize(Lexer *l);

#endif // LEXER_H
