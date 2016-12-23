PROGRAMMING CHALLENGES
----------------------

### Introduction

This repository is a collection of all the programming challenges I've worked on. I hope to grow it significantly in time. All programs will be listed here, chronologically.

### Trolls - [Link](https://www.reddit.com/r/dailyprogrammer/comments/4vrb8n/weekly_25_escape_the_trolls/)

* **Language**: C++
* **Synopsis**: My first attempt to do some recreational programming. The player moves around a maze, trying to avoid trolls and reach the X. The player can push walls that are 1 unit thick.
* **How To Play**: 
    - Running the game:
        * Compile the game with `g++ -lncurses main.cpp --output trolls`.
        * Run the game with `./trolls`.
    - Menu
        * Use the arrow keys to browse the menu, and `Enter` to select an option. 
        * Left and right on the arrow keys allow you to change the size of the map and number of trolls
    - In-game
        * Use the arrow keys move your character throughout the maze.
        * There is an arrow, '-', lying in the maze, walk over it to pick it up!
            - You can then press `Space` to fire the arrow ahead of yourself, killing any trolls in its path!
            - You can reclaim the fallen arrow and re-use it
        * The game ends when a troll reaches you, or you reach the end of the maze.
        * You can press `Esc` at any time to exit the game.
* **Notes**: 
    - The game is rendered via ncurses, thus getting this game to work on Windows is probably more effort than it's worth. 
    - You may use `h`, `j`, `k`, `l` instead of the arrow keys, just as they are used in vim.
