// main.cpp

#include <iostream>
#include "Scene.h"
#include "Sprite.h"

/** 
 *  This is the main loop for the game. Add event handling here
 *  \param Scene* scene
 */
void startMainLoop(Scene* scene, Sprite* floor){
    // start the main game loop
    bool midJump = false;
    Sprite *player = scene->getSprites()->at(0);
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
                            player->addForce("left", 10);
                            break;
                        case SDLK_RIGHT:
                            player->addForce("right", 10);
                            break;
                        case SDLK_UP:
                            if(!midJump && player->collidesWith(floor)){
                                player->addForce("up", 15);
                                midJump = true;
                            }             
                            break;
                        case SDLK_DOWN:
                            if(player->collidesWith(floor) != true){
                                player->addForce("down", 10);
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
                            /* We check to make sure the sprite is moving */
                            /* to the left. If it is then we zero the    */
                            /* velocity. If the sprite is moving to the   */
                            /* right then the right key is still press   */
                            /* so we don't tocuh the velocity            */
                            if( player->getDeltaPosition()->at("dx") < 0 )
                                player->setDeltaXPosition(0);
                            break;
                        case SDLK_RIGHT:
                            if( player->getDeltaPosition()->at("dx") > 0 )
                                player->setDeltaXPosition(0);
                            break;
                        case SDLK_UP:
                            midJump = false;
                            if( player->getDeltaPosition()->at("dy") < 0 )
                                player->setDeltaYPosition(0);
                            break;
                        case SDLK_DOWN:
                            if( player->getDeltaPosition()->at("dy") > 0 )
                                player->setDeltaYPosition(0);
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
        scene->clear();
        for(int index = 0; index < scene->getSprites()->size(); index++){
            scene->getSprites()->at(index)->update();
            scene->getSprites()->at(index)->draw();
        }
        floor->update();
        floor->draw();
        scene->refresh();
        if(player->collidesWith(floor) == true){
            player->setDeltaYPosition(0);
        }
        if(player->collidesWith(floor) == false){
            player->addForce("down", 1);
        }
        
        std::cout << "\r" << "DEBUG: " << player->getPosition()->at("xPos") << " : " << player->getPosition()->at("yPos") << " | " << player->getDeltaPosition()->at("dx") << " : " << player->getDeltaPosition()->at("dy") << " --> {" << player->collidesWith(floor) << "} --> Err: [" << SDL_GetErrorMsg << "] --- Num Sprites{" << scene->getSprites()->size() << "}                      ";

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

    Sprite* player = new Sprite(scene, "pixil-frame-0.png");
    player->setPosition(50, 50);
    player->setSize(100, 100);
    player->draw();
    scene->addSprite(player);

    Sprite* floor = new Sprite(scene, "Baby Yoda.png");
    floor->setPosition(100, 300);
    floor->setSize(600, 20);
    floor->draw();

    startMainLoop(scene, floor);
    scene->quit(); //when mainLoop terminates quit the game
    return(0);
}