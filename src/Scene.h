// Scene.h

#ifndef _SCENE_H_
#define _SCENE_H_

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>
#include "SDL_image.h"

class Sprite;

class Scene{
    private:
        SDL_Window* window_;
        SDL_Event* event_;
        char* gameName_;
        std::unordered_map<std::string, int>* backgroundColor_;
        std::unordered_map<std::string, int>* size_;
        SDL_Rect* boundsRect_;
        //std::unordered_map<std::string, int>* position_;
        std::vector<Sprite*>* sprites_;
        int frameRate_;
        std::list<bool>* keyStates_;
        bool mouseButtonState_;
        bool isShowing_;

    public:
        // static member variable
        static SDL_Renderer *renderer;

        // Constructors
        Scene();
        Scene(Scene*);

        // Deconstructor
        ~Scene();

        // Getters and Setters
        SDL_Window *getWindow();
        void setWindow(SDL_Window *);
        SDL_Event *getEvent();
        void setEvent(SDL_Event *);
        char* getGameName(void);
        void setGameName(char*);
        std::unordered_map<std::string, int> *getBackgroundColor(void);
        void setBackgroundColor(int, int, int);
        std::unordered_map<std::string, int>* getSize(void);
        void setSize(int height, int width);
        SDL_Rect* getBoundsRect();
        void setBoundsRect(SDL_Rect*);
        //std::unordered_map<std::string, int>* getPosition(void);
        //void setPosition(int xPos, int yPos);
        std::vector<Sprite*>* getSprites(void);
        void setSprites(std::vector<Sprite*>*);
        int getFrameRate(void);
        void setFrameRate(int);
        std::list<bool>* getKeyStates(void);
        void setKeyStates(std::list<bool>*);
        bool getMouseClickState(void);

        // Methods
        void initializeGraphics();
        void addSprite(Sprite*);
        void start();
        void end();
        void pause();
        void clear();
        void refresh();
        void hideCursor();
        void showCursor();
        void getMousePos();
        void hide();
        void show();
        void quit();
        

}; // end class declaration

#endif