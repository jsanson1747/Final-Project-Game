//MapManager.h

#ifndef _MapManager_H_
#define _MapManager_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Scene.h"
#include "Sprite.h"

class Scene;

class MapManager{
    private:
        int tileSize_;
        const char* tileFilePrefix_;
        Scene* scene_;
        const char* mapFile_;
        std::vector<std::vector<int>>* mapVector_;
        std::vector<std::string>* imgVector_;
        std::vector<SDL_Texture*>* textureVector_;
        int numCols_;
        int numRows_;
        std::vector<std::vector<int>>* parseTMX(const char*);

    public:
        MapManager(int, const char*, Scene*, const char*);
        ~MapManager();
        int getTileSize(void);
        void setTileSize(int);
        const char* getTileFilePrefix(void);
        void setTileFilePrefix(const char*);
        Scene* getScene(void);
        const char* getMapFile(void);
        void setMapFile(const char*);
        void loadMap(void);
        void drawMap(void);
        bool inBounds(SDL_Rect*);
        std::vector<std::vector<int>>* getMapVector(void);

}; //end class declaration

#endif
