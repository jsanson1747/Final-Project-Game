// main.cpp

#include <iostream>
#include "Scene.h"
#include "Sprite.h"

/** 
 *  This is the main loop for the game. Add event handling here
 *  \param Scene* scene
 */
void startMainLoop(Scene* scene, Sprite* sprite, Sprite* floor){
    // start the main game loop
    SDL_Event *event = scene->getEvent();
    bool isRunning = true;
    int maxFPS = 60;
    int desiredDelta = 1000 / maxFPS;
    while(isRunning){
        int startLoop = SDL_GetTicks();
        while( SDL_PollEvent(event) ){ // Check for events
            switch(event->type){
                case SDL_QUIT: //check for user to close program
                    isRunning = false;
                
                case SDL_KEYDOWN: // Look for a keypress
                    switch( event->key.keysym.sym ){ // Check the SDLKey values and move change the coords
                        case SDLK_LEFT:
                            sprite->addForce("left", 10);
                            break;
                        case SDLK_RIGHT:
                            sprite->addForce("right", 10);
                            break;
                        case SDLK_UP:
                            sprite->addForce("up", 15);
                            break;
                        case SDLK_DOWN:
                            if(sprite->collidesWith(floor) != true){
                                sprite->addForce("down", 10);
                                break;
                            }
                        default:
                            break;
                    }
                    break;
                /* We must also use the SDL_KEYUP events to zero the x */
                /* and y velocity variables. But we must also be       */
                /* careful not to zero the velocities when we shouldn't*/
                case SDL_KEYUP:
                    switch( event->key.keysym.sym ){
                        case SDLK_LEFT:
                            /* We check to make sure the alien is moving */
                            /* to the left. If it is then we zero the    */
                            /* velocity. If the alien is moving to the   */
                            /* right then the right key is still press   */
                            /* so we don't tocuh the velocity            */
                            if( sprite->getDeltaPosition()->at("dx") < 0 )
                                sprite->setDeltaXPosition(0);
                            break;
                        case SDLK_RIGHT:
                            if( sprite->getDeltaPosition()->at("dx") > 0 )
                                sprite->setDeltaXPosition(0);
                            break;
                        case SDLK_UP:
                            if( sprite->getDeltaPosition()->at("dy") < 0 )
                                sprite->setDeltaYPosition(0);
                            break;
                        case SDLK_DOWN:
                            if( sprite->getDeltaPosition()->at("dy") > 0 )
                                sprite->setDeltaYPosition(0);
                            break;
                        default:
                            break;
                    }
                    break;
                
                default:
                    break;
            }
        }

        //////////////////////////////
        // Add update handling here //
        //////////////////////////////
        sprite->update();
        floor->update();
        scene->clear();
        sprite->draw();
        floor->draw();
        scene->refresh();
        if(sprite->collidesWith(floor) == true){
            sprite->setDeltaYPosition(0);
        }
        if(sprite->collidesWith(floor) == false){
            sprite->addForce("down", 1);
        }
        std::cout << "\r" << "DEBUG: " << sprite->getPosition()->at("xPos") << " : " << sprite->getPosition()->at("yPos") << " | " << sprite->getDeltaPosition()->at("dx") << " : " << sprite->getDeltaPosition()->at("dy") << " --> {" << sprite->touchingFloor(floor) << "} --> Err: [" << SDL_GetErrorMsg << "]                      ";

        int delta = SDL_GetTicks() - startLoop;
        if(delta < desiredDelta){
            SDL_Delay(desiredDelta - delta);
        } //end if
    }        
} //end mainLoop

int main(int argv, char** args){
    Scene* scene = new Scene();
    scene->setBackgroundColor(200, 200, 200);
    scene->setGameName("Awesome Game");
    scene->initializeGraphics();

    Sprite* sprite = new Sprite(scene, "pixil-frame-0.png");    
    sprite->setPosition(50, 50);
    sprite->setSize(100, 100);
    sprite->draw();

    Sprite* floor = new Sprite(scene, "Baby Yoda.png");
    floor->setPosition(100, 300);
    floor->setSize(600, 20);
    floor->draw();

    startMainLoop(scene, sprite, floor);
    scene->quit(); //when mainLoop terminates quit the game
    return(0);
}