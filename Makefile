CC=gcc
CFLAGS=-Wall
HEADERS=headers/
SRC=src/
RELEASE=release/src/
EXEC=release/spaceinvaders

all: $(EXEC)

$(EXEC): release/main.o $(RELEASE)spaceship.o
	$(CC) -o $(EXEC) $^ $(CFLAGS)

release/main.o: main.c $(HEADERS)*.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

$(RELEASE)spaceship.o: $(SRC)spaceship.c $(HEADERS)spaceship.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(RELEASE)*.o
	rm -rf release/main.o
	rm -rf release/spaceinvaders
