//Player.cpp

#include "Player.h"

void Player::update(){
    if(isShowing() == true){
        int newXPos = getPosition()->at("xPos") + getDeltaPosition()->at("dx");
        int newYPos = getPosition()->at("yPos") + getDeltaPosition()->at("dy");
        setPosition(newXPos, newYPos);
        getCollisionRect()->x = newXPos;
        getCollisionRect()->y = newYPos;
        checkBounds();
    }
} //end update