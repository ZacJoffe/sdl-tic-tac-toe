# SDL Tic-Tac-Toe
Tic-Tac-Toe built in C++ using SDL2.

## About
Back in high school I created a TTT game in Java using an applet. The code is
old and terrible, and I'd like to forget that I ever made it. But TTT is a fun project,
so I rewrote it in C++.

As far as future goals for this project, I'd like to implement a single player
mode using a Minimax AI.

## Build
If you're on Linux, you can use `CMake` to generate a Makefile, then use `Make` to compile the project. Simply type:
```
cmake . && make
```
Run the binary:
```
./ttt
```

You can also compile manually (assuming you have `g++`, `SDL2` and `SDL2_TTF`):
```
g++ ./src/*.cpp -w -lSDL2 -lSDL2_ttf -o ttt && ./ttt
```
