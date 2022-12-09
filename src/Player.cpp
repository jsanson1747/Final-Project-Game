//Player.cpp

#include "Player.h"

void Player::update(){
    if(isShowing() == true){
        int newXPos = getPosition()->at("xPos") + getDeltaPosition()->at("dx");
        int newYPos = getPosition()->at("yPos") + getDeltaPosition()->at("dy");
        setPosition(newXPos, newYPos);

        getCollisionRect()->x = newXPos;
        getCollisionRect()->y = newYPos;

        newXPos = getScene()->getPosition()->at("xPos") + getScene()->getDeltaPosition()->at("dx");
        newYPos = getScene()->getPosition()->at("yPos") + getScene()->getDeltaPosition()->at("dy");

        getScene()->setPosition(newXPos, newYPos);

        checkBounds();
    }
} //end update