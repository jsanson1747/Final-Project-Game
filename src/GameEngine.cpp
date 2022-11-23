// main.cpp

#include <iostream>
#include "Scene.h"
#include "Sprite.h"

/** 
 *  This is the main loop for the game. Add event handling here
 *  \param Scene* scene
 */
void startMainLoop(Scene* scene){
// start the main game loop
bool isRunning = true;
while(isRunning){
    while (SDL_PollEvent(scene->getEvent())){
        switch(scene->getEvent()->type){
        case SDL_QUIT:
            isRunning = false;
            
        //////////////////////////////////
        // Add more event handling here //
        //////////////////////////////////

        } //end switch
    } // end while
} //end while

} //end mainLoop

int main(int argv, char** args){
    Scene* scene = new Scene();
    scene->setGameName("Awesome Game");
    scene->initializeGraphics();

    const char* image_path = "small dude.png";
    Sprite* sprite = new Sprite(scene, image_path);
    
    float counter = 1;
    while(counter < 300){
       sprite->setPosition(50 + counter, 50 + counter);
        sprite->setSize(75, 75);
        sprite->draw();
        counter += 0.1;
    }

    
    //sprite->setPosition(50, 50);
    //sprite->setSize(75, 75);
    //sprite->draw();

    startMainLoop(scene);

    return(0);
}