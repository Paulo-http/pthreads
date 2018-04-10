CC=gcc -std=c99
CFLAGS= −W −Wall
EXEC=run
SRC:= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS= -lm

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(OBJ)