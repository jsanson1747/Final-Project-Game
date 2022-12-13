# Final-Project-Game

## Technology Stack
My game utilizes the C++ graphics libraries SDL2 and SDL_Image. I used my custom game engine as the base and expanded it to meet my game's needs.  

## Launching the game
In orrder to launch the game, close this repository into your personal machine. Then open the folder in VS-Code. Once in VS-Code, run the program and it will automatically use the configuration filed from the .vscode folder to build and run the game.

## Game Structure
![UML drawio](https://user-images.githubusercontent.com/107002749/207442877-0d26def3-8400-4c55-b436-0438720ba0da.png)
The main components of this system are the Sprite and the Scene classes. The sprite class contains all the methods for manipulating sprites and the Scene class is the main control center of the engine. All the event handling is done in the game.cpp file. This allows the programmer to edit what events the engine checks for and what all goes on in the game's main loop. The MapManager class is another critically important aspect of this game engine. It manages the drawing for the entire level. Level data is stored in a textfile as a two-dimensional array that is then parsed by the MapManager. This file is the XML file that was exported from the Tiled Level Editor except that most of the XML has been removed from the file to make parsing easier. Once the map is parsed, it uses the cooresponding array data to create an array of images. At this point, the MapManager can draw the map using this image array and it only has to load and parse the map once every time a new level is needed. This separation between loading and drawing allows the drawMap() function to be quite light and efficient and not put a heavy load on the main loop.

## Gameplay
This game was intended to be a platformer similar to Mario. As of now, I have the platforming mechanics implemented as well as the level scrolling and a very basic level designed. I hope to expand upon this in the future and make it more of a complete game. 
