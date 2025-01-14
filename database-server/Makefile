CC = gcc
CFLAGS = -Wall -O2 -std=c2x
LDFLAGS =

SRC = main.c btree.c database.c
OBJ = $(SRC:.c=.o)
EXEC = database_server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
