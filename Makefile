CC=gcc
CFLAGS=$(ncursesw5-config --cflags --libs) -Wall -lncursesw -lmenu
HEADERS=headers/
SRC=src/
RELEASE=release/src/
EXEC=release/spaceinvaders

all: $(EXEC)

$(EXEC): release/main.o $(RELEASE)spaceship.o $(RELEASE)fieldOfPlay.o $(RELEASE)utils.o $(RELEASE)monsters.o
	$(CC) -o $(EXEC) $^ $(CFLAGS)

release/main.o: main.c $(HEADERS)*.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

$(RELEASE)spaceship.o: $(SRC)spaceship.c $(HEADERS)spaceship.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

$(RELEASE)fieldOfPlay.o: $(SRC)fieldOfPlay.c $(HEADERS)fieldOfPlay.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

$(RELEASE)monsters.o: $(SRC)monsters.c $(HEADERS)monsters.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

$(RELEASE)utils.o: $(SRC)utils.c $(HEADERS)utils.h
	$(CC) -I $(HEADERS) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(RELEASE)*.o
	rm -rf release/main.o
	rm -rf release/spaceinvaders
