// Scene.cpp

#include "Scene.h"

Scene::Scene(){
    //initialize data structures
    this->size_ = new std::unordered_map<std::string, int>;
    this->backgroundColor_ = new std::unordered_map<std::string, int>;
    //position_ = new std::unordered_map<std::string, int>;
    this->sprites_ = new std::list<Sprite*>;
    this->keyStates_ = new std::list<bool>;

    //  initialize map and set default size;
    this->size_->insert({"width", 500});
    this->size_->insert({"height", 500});
    
    // initialize map and set default background color
    this->backgroundColor_->insert({"red", 255});
    this->backgroundColor_->insert({"green", 255});
    this->backgroundColor_->insert({"blue", 255});

    // initialize SDL event detection
    this->event_ = new SDL_Event();

    //Default game name
    this->gameName_ = "Untitled Game";

    //setPosition(0, 0);

} // end default constructor


Scene::Scene(Scene* scene){
    scene->renderer_ = this->renderer_;
    scene->size_ = this->size_;
    //scene->position_ = this->position_;
    scene->sprites_ = this->sprites_;
    scene->frameRate_ = this->frameRate_;
    scene->keyStates_ = this->keyStates_;
    scene->mouseButtonState_ = this->mouseButtonState_;
} //end copy constructor


Scene::~Scene(){
    delete size_;
    //delete position_;
    delete backgroundColor_;
    delete sprites_;
    delete keyStates_;
    delete event_;

} // end deconstructor


SDL_Renderer* Scene::getRenderer(void){
    return(this->renderer_);
} // end getRenderer


void Scene::setRenderer(SDL_Renderer* renderer){
    this->renderer_ = renderer;
} // end renderer


SDL_Window* Scene::getWindow(void){
    return(this->window_);
} // end getWindow


void Scene::setWindow(SDL_Window* window){
    this->window_ = window;
} // end setWindow


SDL_Event* Scene::getEvent(void){
    return(this->event_);
} // end getEvent


void Scene::setEvent(SDL_Event* event){
    this->event_ = event;
} // end setEvent


char* Scene::getGameName(void){
    return (this->gameName_);
} //end getGameName


void Scene::setGameName(char* gameName){
    this->gameName_ = gameName;
} // end setGameName


std::unordered_map<std::string, int>* Scene::getBackgroundColor(void){
    return (this->backgroundColor_);
} // end getBackgroundColor


void Scene::setBackgroundColor(int red, int green, int blue){
    this->backgroundColor_->at("red") = red;
    this->backgroundColor_->at("green") = green;
    this->backgroundColor_->at("blue") = blue;
} // end setBackgroundColor


std::unordered_map<std::string, int>* Scene::getSize(void){
    return(size_);
} // end getSize


void Scene::setSize(int width, int height){
    this->size_->at("width") = width;
    this->size_->at("height") = height;
} // end setSize


//std::unordered_map<std::string, int>* Scene::getPosition(void){
//
//} // end getPosition


//void Scene::setPosition(int xPos, int yPos){
//    size_->at({"xPos", xPos});
//    size_->at({"yPos", yPos});
//} // end setPosition


std::list<Sprite*>* Scene::getSprites(void){
    return (sprites_);
} // getSprites


void Scene::setSprites(std::list<Sprite*>* sprites){
    this->sprites_ = sprites;
} // end setSprites


int Scene::getFrameRate(void){
    return (this->frameRate_);
} // end getFrameRate


void Scene::setFrameRate(int frameRate){
    this->frameRate_ = frameRate;
} // end setFrameRate


std::list<bool>* Scene::getKeyStates(void){
    return (this->keyStates_);
} // end getKeyStates


void Scene::setKeyStates(std::list<bool>* keyStates){
    this->keyStates_ = keyStates;
} // end setKeyStates


bool Scene::getMouseClickState(void){
    return (this->mouseButtonState_);
} // end getMouseClickState


void Scene::initializeGraphics(void){
    // initialize graphics engine
    SDL_Init(SDL_INIT_EVERYTHING);
    // initialize SDL image extension
    IMG_Init(IMG_INIT_PNG);
    // initialize components
    SDL_Window* window = SDL_CreateWindow(getGameName(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size_->at("width"), size_->at("height"), 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    setRenderer(renderer);
    setWindow(window);
} // end initializeGraphics

void Scene::start(){

} // end start


void Scene::end(){
    
} // end end


void Scene::pause(){

} // end pause


void Scene::clear(){
    int red = getBackgroundColor()->at("red");
    int green = getBackgroundColor()->at("green");
    int blue = getBackgroundColor()->at("blue");
    int alpha = SDL_ALPHA_OPAQUE;
    // clear the canvas with the background color
    SDL_SetRenderDrawColor(getRenderer(), red, green, blue, alpha);
    SDL_RenderClear(getRenderer());
} // end clear


void Scene::hideCursor(){

} // end hideCursor


void Scene::showCursor(){

} // end showCursor


void Scene::getMousePos(){

} // end getMousePos()


void Scene::hide(){

} // end hide


void Scene::show(){

} // end show

void Scene::quit(void){
    SDL_DestroyRenderer(getRenderer());
    SDL_DestroyWindow(getWindow());
    SDL_Quit();
    IMG_Quit();
}