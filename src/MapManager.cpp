//MapManager.cpp

#include "MapManager.h"

MapManager::MapManager(int tileSize, const char* tileFilePrefix, Scene* scene, const char* mapFile){
    this->tileSize_ = tileSize;
    this->tileFilePrefix_ = tileFilePrefix;
    this->scene_ = scene;
    this->mapFile_ = mapFile;

} //end default constructor

MapManager::~MapManager(){
    delete this->mapVector_;
    delete this->imgVector_;
} //end deconstructor

int MapManager::getTileSize(void){
    return this->tileSize_;
} //end getTileSize

void MapManager::setTileSize(int size){
    this->tileSize_ = size;
} //end setTileSize

const char* MapManager::getTileFilePrefix(void){
    return this->tileFilePrefix_;
} //end getTileFileStart

void MapManager::setTileFilePrefix(const char* prefix){
    this->tileFilePrefix_ = prefix;
} //setTileFileStart

Scene* MapManager::getScene(void){
    return this->scene_;
} //end getScene

const char* MapManager::getMapFile(void){
    return this->mapFile_;
} //end getMap

void MapManager::setMapFile(const char* mapFile){
    this->mapFile_ = mapFile;
} //end setMap

std::vector<std::vector<int>>* MapManager::getMapVector(void){
    return this->mapVector_;
} //end getMapVector

void MapManager::loadMap(void){
    SDL_Surface* surface;
    SDL_Texture* texture;
    this->imgVector_ = new std::vector<std::string>;
    this->textureVector_ = new std::vector<SDL_Texture*>;
    std::string completeFilePath = "";
    std::vector<int>* innerVector= new std::vector<int>;
    this->mapVector_ = parseTMX(getMapFile());
    for (int row = 0; row < this->numRows_; row++){
        innerVector = &mapVector_->at(row);
        for (int col = 0; col < this->numCols_; col++){
            completeFilePath = "";
            completeFilePath += getTileFilePrefix() + std::to_string(innerVector->at(col)) + ".png";
            this->imgVector_->push_back(completeFilePath);
            surface = IMG_Load(completeFilePath.c_str());
            texture = SDL_CreateTextureFromSurface(Scene::renderer, surface);
            this->textureVector_->push_back(texture);
        } // end for
    } // end for
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

} // end loadMap

std::vector<std::vector<int>>* MapManager::parseTMX(const char* file){
    std::vector<std::vector<int>>* outerVector = new std::vector<std::vector<int>>;
    std::vector<int> *innerVector = new std::vector<int>;
    std::string row;
    int width, height;

    std::ifstream fin;
    fin.open(file);
    fin >> width >> height;
    int mapData[width][height];

    for(int currentRow = 0; currentRow < height; currentRow++){
        fin >> row;
        int currentCol = 0;
        int index = 0;
        std::string buffer = "";
        while(currentCol <= row.length()){
            if(row[currentCol] != ','){
                buffer += row[currentCol];
            } //end if
            else{
                mapData[index][currentRow] = std::stoi(buffer);
                index++;
                buffer = "";
            }
            currentCol++;
        } //end while
        mapData[index][currentRow] = std::stoi(buffer);
    } //end for
    fin.close();

    this->numCols_ = width;
    this->numRows_ = height;

    for(int currentRow = 0; currentRow < height; currentRow++){
        for (int currentCol = 0; currentCol < width; currentCol++){
            innerVector->push_back(mapData[currentCol][currentRow]);
        } //end for
        outerVector->push_back(*innerVector);
        innerVector->clear();
    } //end for

    return outerVector;
} //end parseTMX


void MapManager::drawMap(void){
    Sprite* player = getScene()->getSprites()->at(0);
    SDL_Rect* dest = new SDL_Rect();
    dest->x = getScene()->getPosition()->at("xPos");
    dest->y = 0;
    dest->w = this->getTileSize();
    dest->h = this->getTileSize();
    int counter = 0;
    for (int row = 0; row < this->numRows_; row++){
        dest->x = getScene()->getPosition()->at("xPos");
        for (int index = 0; index < numCols_; index++){
            if(this->imgVector_->at(counter).c_str() != 0){
                if(inBounds(dest)){
                    SDL_RenderCopy(Scene::renderer, this->textureVector_->at(counter), NULL, dest);
                    dest->x += getTileSize();
                } //end if
            } //end if
            counter++;
        } //end for
        dest->y += getTileSize();
    } // end for
    delete dest;
} //end drawMap


bool MapManager::inBounds(SDL_Rect* rect){
    SDL_Rect* border = getScene()->getBoundsRect();
    if(rect->x < border->x | rect->x > border->x + border->w){
        return false;
    } //end if
    if(rect->y < border->y | rect->y > border->y + border->h){
        return false;
    } //end if
    return true;
} //end inBounds