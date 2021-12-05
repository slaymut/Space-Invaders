# Space-Invaders
Space Invaders Project for ESIEA Engineer School in C langage.


## WHAT TO INSTALL BEFORE PLAYING THE GAME
This game is using the ncurses library in order to use its windows and graphics. We also use a few other libraries for the sound, like "sox" !

Here are the commands you'll have to run:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```
```bash
sudo apt-get install sox
sudo apt-get install libsox-fmt-mp3
sudo apt-get install libcurl4-openssl-dev libsox-dev
```


## HOW TO RUN THE PROGRAM AND PLAY THE GAME

All you have to do to launch the game is first to compile, then launch the executable created in the /release folder.

### Compile 
```bash
make
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