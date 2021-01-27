#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "../libs/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetmanager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
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
	if (TTF_Init() != 0) {
		std::cerr << "Error Initializing SDL TTF." << std::endl;
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

	debug = false;

	LoadLevel(0);

	isRunning = true;
	return;
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
	//Start including new assets to the assetmanager map
	assetmanager->AddTexture("tank-image", std::string("./assets/images/tank-tiger-right.png").c_str());
	assetmanager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetmanager->AddTexture("radar-image", std::string("./assets/images/radar-spritesheet.png").c_str());
	assetmanager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
	assetmanager->AddTexture("heliport-image", std::string("./assets/images/base-landing.png").c_str());
	assetmanager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);


	//Start including entities and also components to them

	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);


	Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

	Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
	heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	heliport.AddComponent<SpriteComponent>("heliport-image");
	heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

	Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE_COLOR);




	//SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {


	manager.ListAllEntities();

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

	HandleCameraMovement();
	CheckCollisions();
	//std::cout << "Time: " << (static_cast<int>(SDL_GetTicks() / 1000)) << std::endl;
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

void Game::HandleCameraMovement() {
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	//Clamping of camera
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;

}

void Game::CheckCollisions() {
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == CollisionType::PLAYER_ENEMY_COLLISION) {
		ProcessGameOver();
	}
	if (collisionType == CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION) {
		ProcessNextLevel(1);
	}
}

void Game::ProcessNextLevel(int Level) {
	std::cout << "\nNext level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver() {
	std::cout << "\nGame over" << std::endl;
	isRunning = false;
}



void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
