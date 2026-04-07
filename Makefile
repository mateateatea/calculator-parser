FILES = src/main.c src/calc.c src/gui.c src/parser.c
CC = gcc
CFLAGS = -Wall -Wextra -I include

ifeq ($(OS), Windows_NT)
	TARGET = calculator_with_parser.exe
	LIBS =
else
	TARGET = calculator_with_parser
	LIBS = -lm
endif

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
