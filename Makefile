#pour executer il faut faire ./metro metro.txt 

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

OBJ = src/main.o src/station.o src/graphe.o src/menu.o

metro: $(OBJ)
	$(CC) $(OBJ) -o metro

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o metro

