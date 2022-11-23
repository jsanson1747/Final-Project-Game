// Sprite.h

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "Scene.h"


class Sprite{
    private:
        SDL_Surface* image_;
        std::unordered_map<std::string, int>* size_;
        std::unordered_map<std::string, int>* position_;
        int imageAngle_;
        int moveAngle_;
        int speed_;
        std::unordered_map<std::string, int>* deltaPosition_; // change in position
        std::unordered_map<std::string, int>* deltaVelocity_; // change in velocity (acceleration)
        Scene* scene_;
        std::string boundAction_; // what the sprite does when it detects a boundry
        SDL_Rect* imgRect_;
        SDL_Rect *collisionRect_;

        //internal helper method
        void vectorProject();

    public:
        // Constructors
        Sprite(Scene*, const char*);
        Sprite(Sprite*);
        
        // Deconstructor
        ~Sprite();

        //Getters and Setters
        SDL_Surface* getImage(void);
        void setImage(const char*);
        void setImage(SDL_Surface*);
        std::unordered_map<std::string, int>* getSize(void);
        void setSize(int, int);
        std::unordered_map<std::string, int> *getPosition(void);
        void setPosition(int, int);
        int getImageAngle(void);
        void setImageAngle(int);
        int getMoveAngle(void);
        void setMoveAngle(int);
        int getSpeed(void);
        void setSpeed(int);
        std::unordered_map<std::string, int>* getDeltaPosition(void);
        void setDeltaPosition(int dx, int dy);
        std::unordered_map<std::string, int>* getDeltaVelocity(void);
        void setDeltaVelocity(int ddx, int ddy);
        Scene* getScene(void);
        void setScene(Scene*);
        std::string getBoundAction(void);
        void setBoundAction(std::string);
        SDL_Rect *getImgRect(void);
        void setImgRect(SDL_Rect *);
        SDL_Rect *getCollisionRect(void);
        void setCollisionRect(SDL_Rect *);

        //methods
        void draw();
        virtual void update();
        void hide();
        void show();
        void addForce(std::string, int);
        void checkBounds();
        bool collidesWith(Sprite*);
        bool touchingFloor(Sprite* otherSprite);
        int distanceTo(Sprite*);
        int angleTo(Sprite *);
        void setDeltaXPosition(int);
        void setDeltaYPosition(int);
        void setDeltaXVelocity(int);
        void setDeltaYVelocity(int);

}; // end class declariation 

#endif