#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../libs/sol/sol.hpp"
#include "./Entity.h"
#include "Component.h"
#include "EntityManager.h"

class AssetManager;

class Game {
	private:
		bool isRunning;
		SDL_Window* window;
	public:
		Game();
		~Game();
		inline static bool debug;
		int ticksLastFrame = 0;
		bool IsRunning() const;
		static SDL_Renderer* renderer;
		static AssetManager* assetmanager;
		static SDL_Event event;
		static SDL_Rect camera;
		void LoadLevel(int levelNumber);
		void Initialize(int width, int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();
		void HandleCameraMovement();
		void CheckCollisions();
		void ProcessNextLevel(int levelNumber);
		void ProcessGameOver();

};

#endif // !GAME_H
