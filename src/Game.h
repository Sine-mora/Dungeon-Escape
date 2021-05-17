#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "sol.hpp"
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class AssetManager;

class Game {
    private:
        bool isRunning;
        SDL_Window *window;
    public:
        Game();
        ~Game();
        int ticksLastFrame = 0;
        bool IsRunning() const;
        static SDL_Renderer *renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        bool LoadLevel(int levelNumber);
        bool Initialize(int width, int height);
        void ProcessInput();
        void ProcessNextLevel(int levelNumber);
        void ProcessGameOver();
        void Update();
        void Render();
        void Destroy();
        void HandleCameraMovement();
        void CheckCollisions();
};

#endif
