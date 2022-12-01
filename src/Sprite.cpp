// Sprite.cpp

#include <iostream>
#include "Sprite.h"

Sprite::Sprite(Scene* scene, const char* file){
    setScene(scene);
    setImage(file);

    // initialize data structures
    this->size_ = new std::unordered_map<std::string, int>;
    this->position_ = new std::unordered_map<std::string, int>;
    this->deltaPosition_ = new std::unordered_map<std::string, int>;
    this->deltaVelocity_ = new std::unordered_map<std::string, int>;
    this->imgRect_ = new SDL_Rect();
    this->collisionRect_ = new SDL_Rect();

    // initialize map and set default size;
    this->size_->insert({"width", getImage()->w});
    this->size_->insert({"height", getImage()->h});
    imgRect_->w = this->size_->at("width");
    imgRect_->h = this->size_->at("height");

    // initialize map and set default position;
    this->position_->insert({"xPos", 0});
    this->position_->insert({"yPos", 0});
    imgRect_->x = this->position_->at("xPos");
    imgRect_->y = this->position_->at("yPos");

    // initialize map and set default deltaPosition;
    this->deltaPosition_->insert({"dx", 0});
    this->deltaPosition_->insert({"dy", 0});

    // initialize map and set default deltaVelocity;
    this->deltaVelocity_->insert({"ddx", 0});
    this->deltaVelocity_->insert({"ddy", 0});

    // initialize collision box
    this->collisionRect_->x = this->position_->at("xPos");
    this->collisionRect_->y = this->position_->at("yPos");
    this->collisionRect_->w = this->size_->at("width");
    this->collisionRect_->h = this->size_->at("height");

} // end default constructor

Sprite::Sprite(Sprite* sprite){

} // end copy constructor

Sprite::~Sprite(){
    delete this->size_;
    delete this->position_;
    delete this->deltaPosition_;
    delete this->deltaVelocity_;
    SDL_FreeSurface(getImage());
} // end destructor


SDL_Surface* Sprite::getImage(void){
    return (this->image_);
} // end getImage


void Sprite::setImage(const char* file){
    this->image_ = IMG_Load(file);
    //this->image_->h // TODO make this affected by the Sprite's size
} // end setImage

void Sprite::setImage(SDL_Surface* surface){
    this->image_ = surface;
}


std::unordered_map<std::string, int>* Sprite::getSize(void){
    return (size_);
} // end getSize


void Sprite::setSize(int width, int height){
    this->size_->at("width") = width;
    this->size_->at("height") = height;
    this->imgRect_->w = this->size_->at("width");
    this->imgRect_->h = this->size_->at("height");
    this->collisionRect_->w = this->size_->at("width");
    this->collisionRect_->h = this->size_->at("height");

} // end setSize


std::unordered_map<std::string, int>* Sprite::getPosition(void){
    return (this->position_);
} // end getPosition


void Sprite::setPosition(int xPos, int yPos){
    this->position_->at("xPos") = xPos;
    this->position_->at("yPos") = yPos;
    this->imgRect_->x = this->position_->at("xPos");
    this->imgRect_->y = this->position_->at("yPos");
    this->collisionRect_->x = this->position_->at("xPos");
    this->collisionRect_->y = this->position_->at("yPos");
} // end setPosition


int Sprite::getImageAngle(void){
    return (this->imageAngle_);
} // end getImageAngle


void Sprite::setImageAngle(int imageAngle){
    this->imageAngle_ = imageAngle;
} // end setImageAngle


int Sprite::getMoveAngle(void){
    return (this->moveAngle_);
} //end getMoveAngle


void Sprite::setMoveAngle(int moveAngle){
    this->moveAngle_ = moveAngle;
} // end setMoveAngle


int Sprite::getSpeed(void){
    return (this->speed_);
} // end getSpeed


void Sprite::setSpeed(int speed){
    this->speed_ = speed;
} // end setSpeed


std::unordered_map<std::string, int>* Sprite::getDeltaPosition(void){
    return (this->deltaPosition_);
} // end getDeltaPosition


void Sprite::setDeltaPosition(int dx, int dy){
    this->deltaPosition_->at("dx") = dx;
    this->deltaPosition_->at("dy") = dy;
} // end setDeltaPosition


void Sprite::setDeltaXPosition(int dx){
    this->deltaPosition_->at("dx") = dx;
} // end setDeltaXPosition


void Sprite::setDeltaYPosition(int dy){
    this->deltaPosition_->at("dy") = dy;
} // end setDeltaYPosition


std::unordered_map<std::string, int>* Sprite::getDeltaVelocity(void){
    return (this->deltaVelocity_);
} // end getDeltaVelocity


void Sprite::setDeltaVelocity(int ddx, int ddy){
    this->deltaVelocity_->at("ddx") = ddx;
    this->deltaVelocity_->at("ddy") = ddy;
} // end setDeltaVelocity


void Sprite::setDeltaXVelocity(int ddx){
    this->deltaVelocity_->at("ddx") = ddx;
} // end setDeltaXPosition


void Sprite::setDeltaYVelocity(int ddy){
    this->deltaVelocity_->at("ddy") = ddy;
} // end setDeltaYPosition


Scene* Sprite::getScene(void){
    return (this->scene_);
} // end getScene


void Sprite::setScene(Scene* scene){
    this->scene_ = scene;
} // end setScene


std::string Sprite::getBoundAction(void){
    return (this->boundAction_);
} // end getBoundAction


void Sprite::setBoundAction(std::string boundAction){
    this->boundAction_ = boundAction;
} // end setBoundAction


SDL_Rect*  Sprite::getImgRect(void){
    return (this->imgRect_);
} // end getImgRect


void Sprite::setImgRect(SDL_Rect* rect){
    this->imgRect_ = rect;
} // end setImgRect


SDL_Rect*  Sprite::getCollisionRect(void){
    return (this->collisionRect_);
} // end getCollisionRect


void Sprite::setCollisionRect(SDL_Rect* rect){
    this->collisionRect_ = rect;
} // end setCollisionRect


void Sprite::draw(){
    SDL_Texture* texture = SDL_CreateTextureFromSurface(getScene()->getRenderer(), getImage());
    SDL_RenderCopy(getScene()->getRenderer(), texture, &getImage()->clip_rect, getImgRect()); //this line contains potential for using a sprite sheet
    SDL_DestroyTexture(texture);

} // end draw


void Sprite::update(){ //TODO: make this defined in the subclass of Sprite instead of here as this is technically a virtual function
    int newXPos = getPosition()->at("xPos") + getDeltaPosition()->at("dx");
    int newYPos = getPosition()->at("yPos") + getDeltaPosition()->at("dy");
    setPosition(newXPos, newYPos);
    getCollisionRect()->x = newXPos;
    getCollisionRect()->y = newYPos;
} // end update


void Sprite::hide(){

} // end hide


void Sprite::show(){

} // end show


void Sprite::addForce(std::string direction, int magnitude){
    if(direction == "right"){
        setDeltaXPosition(magnitude);
    }
    if(direction == "left"){
        setDeltaXPosition(magnitude * -1);
    }
    if(direction == "up"){
        setDeltaYPosition(getDeltaPosition()->at("dy") + magnitude * -1);
    }
    if(direction == "down"){
        setDeltaYPosition(getDeltaPosition()->at("dy") + magnitude);
    }
} // end addForce


void Sprite::checkBounds(){

} // end checkBounds


bool Sprite::collidesWith(Sprite* otherSprite){
    SDL_Rect *a = this->getCollisionRect(); // rectangle A
    SDL_Rect *b = otherSprite->getCollisionRect(); // rectangle B

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B
    if( bottomA < topB ){
        return false;
    } //end if
    if( topA > bottomB ){
        return false;
    } // end if
    if( rightA < leftB ){
        return false;
    } // end if
    if( leftA > rightB ){
        return false;
    } //end if

    //If none of the sides from A are outside B
    return true;
} // end collidesWith

int Sprite::distanceTo(Sprite*){
    return 0;
} // end distanceTo


int Sprite::angleTo(Sprite *){
    return 0;
} // end angleTo


void Sprite::vectorProject(){

} // end vectorProject

