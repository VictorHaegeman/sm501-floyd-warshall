CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
EXEC   = floyd

SRC    = src/main.c src/graph.c src/floyd.c src/io.c
OBJ    = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
