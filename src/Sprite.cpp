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
    this->rect_ = new SDL_Rect();

    // initialize map and set default size;
    this->size_->insert({"width", getImage()->w});
    this->size_->insert({"height", getImage()->h});
    rect_->w = this->size_->at("width");
    rect_->h = this->size_->at("height");

    // initialize map and set default position;
    this->position_->insert({"xPos", 0});
    this->position_->insert({"yPos", 0});
    rect_->x = this->position_->at("xPos");
    rect_->y = this->position_->at("yPos");

    // initialize map and set default deltaPosition;
    this->deltaPosition_->insert({"dx", 0});
    this->deltaPosition_->insert({"dy", 0});

    // initialize map and set default deltaVelocity;
    this->deltaVelocity_->insert({"ddx", 0});
    this->deltaVelocity_->insert({"ddy", 0});


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
    this->rect_->w = this->size_->at("width");
    this->rect_->h = this->size_->at("height");

} // end setSize


std::unordered_map<std::string, int>* Sprite::getPosition(void){
    return (this->position_);
} // end getPosition


void Sprite::setPosition(int xPos, int yPos){
    this->position_->at("xPos") = xPos;
    this->position_->at("yPos") = yPos;
    this->rect_->x = this->position_->at("xPos");
    this->rect_->y = this->position_->at("yPos");
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


std::unordered_map<std::string, int>* Sprite::getDeltaVelocity(void){
    return (this->deltaVelocity_);
} // end getDeltaVelocity


void Sprite::setDeltaVelocity(int ddx, int ddy){
    this->deltaVelocity_->at("ddx") = ddx;
    this->deltaVelocity_->at("ddy") = ddy;
} // end setDeltaVelocity


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


void Sprite::draw(){
    SDL_Texture* texture = SDL_CreateTextureFromSurface(getScene()->getRenderer(), getImage());

    SDL_RenderClear(getScene()->getRenderer());
    SDL_RenderCopy(getScene()->getRenderer(), texture, &getImage()->clip_rect, this->rect_); //this line contains potential for using a sprite sheet
    SDL_RenderPresent(getScene()->getRenderer());

} // end draw


void Sprite::update(){

} // end update


void Sprite::hide(){

} // end hide


void Sprite::show(){

} // end show


void Sprite::addForce(){

} // end addForce


void Sprite::checkBounds(){

} // end checkBounds


bool Sprite::collidesWith(Sprite*){
    return 0;
} // end collidesWith


int Sprite::distanceTo(Sprite*){
    return 0;
} // end distanceTo


int Sprite::angleTo(Sprite *){
    return 0;
} // end angleTo


void Sprite::vectorProject(){

} // end vectorProject

