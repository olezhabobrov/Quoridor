# Quoridor
Implementation of the board game Quoridor

## Implementation of the AI 

I created a bot using **minmax algorithm** and to decrease the runtime I added an **alpha-beta pruning**. I achieved the depth of search of 4 with time of calculations less than 1 second

## General rules

 **9x9 table and 2 players on different edges of the board with 10 fences each**

![Alt text](/images/table.PNG?raw=true)

 **The goal is to be the first to reach the opposite line**
 **Each turn a player either place a fence or move the pawn**

The fence is a 2 side-by-side blocks, as it's shown in the image:

![Alt text](/images/entireFence.PNG?raw=true)

To place such fence the player should pick the first block and then the available positions will be highlighted:

![Alt text](/images/higlightedFence.PNG?raw=true)

 **There are 2 restrictions for placing a fence**

The player can't put a fence if:

- it crosses other fences
- there isn't a path to win a game for some player

