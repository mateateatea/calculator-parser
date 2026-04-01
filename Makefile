FILES = src/main.c src/calc.c src/gui.c src/parser.c
CC = gcc
CFLAGS = -Wall -Wextra -I include

calculator_with_parser.exe: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o calculator_with_parser.exe

clean:
	rm -f calculator_with_parser.exe