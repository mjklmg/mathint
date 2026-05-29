interpreter: main.c lexer.c
	gcc -o interpreter main.c lexer.c -Wall -Wextra -g
clean:
	rm -rf interpreter
