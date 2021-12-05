# Space-Invaders
Space Invaders Project for ESIEA Engineer School in C langage.


## WHAT TO INSTALL BEFORE PLAYING THE GAME
This game is using the ncurses library in order to use its windows and graphics

Here are the commands you'll have to run:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```


## HOW TO RUN THE PROGRAM AND PLAY THE GAME

All you have to do to launch the game is first to compile, then launch the executable created in the /release folder.

### Compile 
```bash
make clean && make
```

### Run
```bash
./release/spaceinvaders
```

## HOW TO CONTROL THE SPACESHIP

There are three commands to control the spaceship !

Q: Moving to the left

D: Moving to the right

Spacebar: Shoot !

ESCAPE: To quit the program while running a game !

## WARNING

The game is not very easy and progressive mode gets VERY challenging. Monsters will take a long time to kill at some point so.. Have fun trying hahaha !

Still tho, difficulty augmentation is a thing and you can still win. You will see for yourself anyway.

NOTE: MONSTER ACCELERATION WHEN KILLING MONSTERS IS NOT A THING IN PROGRESSIVE MODE. THE GAME WOULD BE TOO HARD.

SECOND NOTE: I RECOMMEND "make clean" before doing "make", so everything is fresh and clean.
