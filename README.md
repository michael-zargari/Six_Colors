# Six_Colors
clone to the game 6 colors - implemented only in the hexagonal version.

# General Description:
the game "Six Colors" (in the variant with hexagons), The game includes two players - a human player and a computer player.
Every turn the human player choose the color from the Color Bar, there is a 6 colors while two of them can't be choosen - the previous colors that the human player and the computer player choose.
the target in this game is to cover first 50% from the board area, the first player to achieve that WIN!

# Implementation:

## The Computer Choosing Algorithms Implementation:

Easy - Simply chooses a color from the accessible neighbors, and the program proceeds accordingly.

Medium - Among the accessible neighbors, the program selects the color that appears most frequently and proceeds with it.

Hard - Using a depth-first search (DFS) algorithm, the program finds the best path. For each DFS run, it checks which color will be the most common and proceeds with it. The DFS explores the graph, examining the neighbors of neighbors, and so on, to find the most favorable color to choose.

After selecting a color, the program assigns it to the player using a breadth-first search (BFS) by identify accessible nodes based on the chosen color.

## Data Structure Implementation:

I created a generic data structure - an a Template Graph, when each node of the graph holding the following information: a template type representing the shape, a list of neighbors, coordinates on the board, and an ownership (human player, computer player, or none).

## Game Board:

Even though we create the board based on a generic data structure, the board itself simulates a two-dimensional matrix. 
When the game starts, the program cgalculate how many shapes can fit in the given area (defined as a constant in the "Macros" file), by the given size of the radius. 
So, if changing the game's size is needed, all we need to do is to change the "Radius" variable in the "Macros" file.

# other:
- Please note that the difficulty level selection is done by the keyboard keys. by using the keyboard arrows select the desired difficulty level then press Enter.
- The game has a new game button, clicking on it will return us to the menu in order to choose a different difficulty level - in case you have difficulty or the level is too easy.  

