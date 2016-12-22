PROGRAMMING CHALLENGES
----------------------

### Introduction

This repository is a collection of all the programming challenges I've worked on. I hope to grow it significantly in time. All programs will be listed here, chronologically.

### Trolls - [Link](https://www.reddit.com/r/dailyprogrammer/comments/4vrb8n/weekly_25_escape_the_trolls/)

* **Language**: C++
* **Synopsis**: My first attempt to do some recreational programming. The player moves around a maze, trying to avoid trolls and reach the X. The player can push walls that are 1 unit thick.
* **How To Play**: 
    - Compile the game with `g++ -lncurses main.cpp --output trolls`.
    - Run the game with `./trolls`.
    - Use the arrow keys to browse the menu, and `Enter` to select an option. 
    - Use the arrow keys move your character throughout the maze.
    - The game ends when a troll reaches you, or you reach the end of the maze.
* **Notes**: 
    - The game is rendered via ncurses, thus getting this game to work on Windows is probably more effort than it's worth. 
    - Planning on adding dynamically-generated mazes
    - Planning on adding an options screen where one can change the number of trolls and the size of the maze. 
    - Might improve troll AI. (Random movement unless the player is in their line of sight?)
