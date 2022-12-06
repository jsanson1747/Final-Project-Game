//Player.h

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprite.h"
#include "Scene.h"

class Player : public Sprite{
    private:
    public:
        Player(Scene* scene, const char* file) : Sprite(scene, file) {}
        void update(void);

}; //end class declaration

#endif