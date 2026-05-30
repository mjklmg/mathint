#ifndef LEXER_H

#define LEXER_H

#include <stddef.h>
typedef enum Token_Type {
	UNKNOWN = 0,
	EOI,
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

typedef struct Lexer {
	int cursor; // cursor position 0;n
	const char* content; // string thats currently tokenized
} Lexer;

Token_Type set_literal_token_type(char c);

Lexer *initLexer(int cursor, const char* str);

void lexer_eat(Lexer *l);

char* get_token_name(Token *token);

Token *tokenize(Lexer *l);

#endif // LEXER_H
