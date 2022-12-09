// main.cpp

#include <iostream>
#include "MapManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"

class mmsystem;

/** 
 *  This is the main loop for the game. Add event handling here
 *  \param Scene* scene
 */
void startMainLoop(Scene* scene, MapManager* MM){
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
                            scene->addForce("left", 10);
                            break;
                        case SDLK_RIGHT:
                            scene->addForce("right", 10);
                            break;
                        case SDLK_UP:
                            if(!midJump && player->onGround()){
                                player->addForce("up", 15);
                                midJump = true;
                            }             
                            break;
                        case SDLK_DOWN:
                            if(player->onGround() != true){
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
                            if( scene->getDeltaPosition()->at("dx") > 0 )
                                scene->setDeltaXPosition(0);
                            break;
                        case SDLK_RIGHT:
                            if( scene->getDeltaPosition()->at("dx") < 0 )
                                scene->setDeltaXPosition(0);
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
        MM->drawMap();
        for(int index = 0; index < scene->getSprites()->size(); index++){
            if(scene->getSprites()->at(index)->isShowing() == true){
                scene->getSprites()->at(index)->update();
                scene->getSprites()->at(index)->draw();
            }
        }
        scene->refresh();

        if(player->onGround() == true){
            player->setDeltaYPosition(0);
        }
        else if(player->onGround() == false){
            player->addForce("down", 1);
        }
        //if(player->collidesWith(floor) == true){
        //    player->setDeltaYPosition(0);
        //}
        //if(player->collidesWith(floor) == false){
        //    player->addForce("down", 1);
        //}
         
        //std::cout << "\r" << "DEBUG: Player-State: " << player->getPosition()->at("xPos") << " : " << player->getPosition()->at("yPos") << " | " << player->getDeltaPosition()->at("dx") << " : " << player->getDeltaPosition()->at("dy") << " --> {" << player->collidesWith(floor) << "} --> Err: [" << SDL_GetErrorMsg << "] --- Num Sprites{" << scene->getSprites()->size() << "}                      ";

        int delta = SDL_GetTicks() - startLoop;
        if(delta < desiredDelta){
            SDL_Delay(desiredDelta - delta);
        } //end if
    } //end while 
} //end mainLoop


int main(int argv, char** args){
    Scene* scene = new Scene();
    scene->setBackgroundColor(200, 200, 200);
    scene->setGameName("Awesome Game");
    scene->initializeGraphics();

    Sprite* player = new Player(scene, "Sprite-Images/Gooch Prototype-1.png");
    player->setPosition(368, 50);
    player->setSize(100, 100);
    player->setBoundAction("respawn");
    player->draw();
    scene->addSprite(player);

    MapManager *MM = new MapManager(32, "TileSet/1 Tiles/Tile_", scene, "S:/School/IUPUI Senior Year/First Semester/Introduction to 3D Game Graphics/Final Project Game/Levels/lvl1.tmx");
    scene->setMapManager(MM);
    MM->loadMap();
    MM->drawMap();

    SDL_Init(SDL_INIT_AUDIO);
    // load WAV file
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV("Music/Gooch Title Music (Looped).wav", &wavSpec, &wavBuffer, &wavLength);
    // open audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    // play audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    
    startMainLoop(scene, MM);
    scene->quit(); //when mainLoop terminates quit the game
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    return(0);
}