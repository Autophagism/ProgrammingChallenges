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

### Rectangles - [Link](https://www.reddit.com/r/dailyprogrammer/comments/5jpt8v/20161222_challenge_296_intermediate_intersecting/)

* **Language**: Python
* **Synopsis**: Calculates the area of a series of rectangles, each identified with two separate points
* **How To Use**:
    - The program is run with `./rectangles.py point11 point 12 point21 point22`, where point11 and point 12 are two opposite corners of a rectangle, and so on.
        * This may be run for any number of rectangles
        * You may run the bonus challenge from the link with `./rectangles -3,0 1.8,4 1,1 -2.5,3.6 -4.1,5.75 0.5,2 -1.0,4.6 -2.9,-0.8`
* **Notes**:
    - This program does not check for user input, it simply breaks if there is an uneven amount of arguments or non-number arguments passed
    - Rounding errors are left in, not bothering to truncate lest programs with many significant digits or very low values suffer incorrect outputs as a result

### Parentheses - [Link](https://www.reddit.com/r/dailyprogrammer/comments/5llkbj/2017012_challenge_298_easy_too_many_parentheses/)

* **Language**: C++
* **Synopsis**: Strips superfluous brackets from a string
* **How To Use**:
    - Compile with `g++ parentheses.cpp --output parentheses`
    - Run with `./parentheses "((a))()(((b)(cd)))"` (for example)
* **Notes**:
    - The challenge says easy but it was definitely harder than Rectangles

### Parentheses2 - [Link](https://www.reddit.com/r/dailyprogrammer/comments/5m034l/20170104_challenge_298_intermediate_too_many_or/)

* **Language**: C++
* **Synopsis**: Shows you the most recent mismatched parenthesis, if any is found, by showing the output bolded in markdown format
* **How To Use**:
    - Compile with `g++ parentheses2.cpp --output parentheses2`
    - Run with `./parentheses "()(ab))"` (for example)
* **Notes**:
    - This challenge was incredibly easy, especially with access to my previous parenthesis program. It took me about 5 minutes to write and test.
    - It enrages me that this is listed as intermediate while the last was easy

### Mirror Encryption - [Link](https://www.reddit.com/r/dailyprogrammer/comments/4m3ddb/20160601_challenge_269_intermediate_mirror/)

* **Language**: C
* **Synopsis**: A basic encryption/decryption program that works off of a key given by the user. It's best to just read the thread to understand the concept.
* **How To Use**:
    - Running the program:
        * Compile the program with `gcc encrypt.c --output encrypt`.
        * Run it as: `./encrypt "<key>" <message>`
        * For example:


        ./encrypt "   \\\\  /\\    
                     \\
            /         
               \\     \\
             \\        
           /      /   
         \\  /      \\  
              \\       
         \\/           
         /            
                   \  
             \\/       
            /       / " TpnQSjdmZdpoohd
* **Notes**:
    - The actual encryption process was insultingly easy to write and took about 5 minutes, meanwhile I struggled for over an hour trying to get the input to work. Unfortunately, passing a backslash requires entering the character twice so that the program does not interpret them as escape characters.

### War - [Link](https://www.reddit.com/r/dailyprogrammer/comments/6ilyfi/20170621_challenge_320_intermediate_war_card_game/)

* **Language**: Ruby
* **Synopsis**: A simulation of the card game "War"
* **How To Use**:
    - Running the program:
        * `ruby war.rb "1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13 1 2 3 4 5 6 7 8 9 10 11 12 13`
        * You may separate the two players' hands with a newline, it makes no difference
        * Running the program without any arguments will cause a random game to be played
* **Notes**:
    - I'm trying to learn Ruby, I figured this would be a good way to get some practice. I failed an attempt at my first hard problem while using C, so perhaps I'll be trying Ruby on the next one.
