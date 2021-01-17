#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"


#include "../libs/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetmanager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Map* map;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
	return this->isRunning;
}

void Game::Initialize(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error Initializing SDL." << std::endl;
		return;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		std::cerr << "Error Creating SDL window." << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	LoadLevel(0);

	isRunning = true;
	return;
}

void Game::LoadLevel(int levelNumber) {
	//Start including new assets to the assetmanager map
	assetmanager->AddTexture("tank-image", std::string("./assets/images/tank-tiger-right.png").c_str());
	assetmanager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetmanager->AddTexture("radar-image", std::string("./assets/images/radar-spritesheet.png").c_str());
	assetmanager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);


	//Start including entities and also components to them
	Entity& chopperEntity(manager.AddEntity("chopper"));
	chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");

	Entity& tankEntity(manager.AddEntity("tank"));
	tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	


	Entity& radarEntity(manager.AddEntity("radar"));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
	

	//SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
	

	manager.ListAllEntities();

	if (tankEntity.HasComponent<TransformComponent>()) {
		std::cout << " Entity has Component ";
	}
	else std::cout << "Entity has no such component";

	


}

void Game::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
				break;
			}
			break;			
		}
		default: {
			break;
		}
	}
}

void Game::Update() {
	//Sleep the execution until we reach the target frame time in ms
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
	
	//Only call delay if we are too fast to process this frame
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	//Delta time is the difference in ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//Clamp Delta time to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05 : deltaTime;

	//Sets the new ticks for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();

	manager.Update(deltaTime);

}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities()) {
		return;
	}

	manager.Render();

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}