#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/TextLabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"
#include "Components/ProjectileEmitterComponent.h"
#include <glm/glm.hpp>

EntityManager manager;
AssetManager* Game::assetmanager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Entity* mainPlayer = NULL;
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
	try
	{
		LoadLevel(1);
	}
	catch (std::exception e)
	{
		std::cerr << "Failed to load level. e.what(): " << e.what() << "\n";
	}


	isRunning = true;
	return;
}
//Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));
void Game::LoadLevel(int levelNumber) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level" + std::to_string(levelNumber);
	lua.script_file("./assets/scripts/" + levelName + ".lua");
	
	/////////////////////////////////////////////////////////////////
	// LOAD ASSETS FROM LUA CONFIG FILE
	/////////////////////////////////////////////////////////////////	
	sol::table levelData = lua[levelName];
	if (!levelData.valid())
	{
		std::cerr << "lua[levelName: " << levelName << "] is not valid!";
		return;
	}
	sol::table levelAssets = levelData["assets"];
	if (!levelAssets.valid())
	{
		std::cerr << "levelData[\"assets\"] is not valid!";
		return;
	}


	unsigned int assetIndex = 0;
	while (true) {
		sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
		if (existsAssetIndexNode == sol::nullopt) {
			break;
		} else {
			sol::table asset = levelAssets[assetIndex];
			if (!asset.valid())
			{
				std::cerr << "levelAssets[assetIndex: " << assetIndex << "] is not valid!";
				return;
			}
			std::string assetType = asset["type"];
			if (assetType.compare("texture") == 0) {
				std::string assetId = asset["id"];
				std::string assetFile = asset["file"];
				assetmanager->AddTexture(assetId, assetFile.c_str());
			}
			if (assetType.compare("font") == 0) {
				std::string assetId = asset["id"];
				std::string assetFile = asset["file"];
				int fontSize = asset["fontSize"];
				assetmanager->AddFont(assetId, assetFile.c_str(), fontSize);
			}
		}
		assetIndex++;
	}

	//////////////////////////////////////////////////////////////////////////
	// LOAD MAP AND TILE INFORMATION FROM LUA CONFIG FILE
	//////////////////////////////////////////////////////////////////////////	
	sol::table levelMap = levelData["map"];
	if (!levelMap.valid())
	{
		std::cerr << "levelData[\"map\"] is not valid!";
		return;
	}
	std::string mapTextureId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];

	map = new Map(
		mapTextureId,
		static_cast<int>(levelMap["scale"]),
		static_cast<int>(levelMap["tileSize"])
	);

	map->LoadMap(
		mapFile,
		static_cast<int>(levelMap["mapSizeX"]),
		static_cast<int>(levelMap["mapSizeY"])
	);

	///////////////////////////////////////////////////////////////////////////
	// LOAD ENTITIES
	///////////////////////////////////////////////////////////////////////////
	sol::table levelEntities = levelData["entities"];

	unsigned int entityIndex = 0;
	while (true) {
		sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
		if (existsEntityIndexNode == sol::nullopt) {
			break;
		}
		else {
			sol::table entity = levelEntities[entityIndex];
			if (!entity.valid())
			{

				std::cerr << "levelEntities[entityIndex: " << entityIndex << "] is not valid!";
				return;
			}
			std::string entityName = entity["name"];
			LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

			//Add new Entity
			auto& newEntity(manager.AddEntity(entityName, entityLayerType));

			//Add Transform Component
			sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
			if (existsTransformComponent != sol::nullopt) {
				auto posX = entity["components"]["transform"]["position"]["x"];
				if (!posX.valid())
				{
					std::cerr << "entityName: " << entityName << " posX not valid!";
					return;
				}
				auto posY = entity["components"]["transform"]["position"]["y"];
				if (!posY.valid())
				{
					std::cerr << "entityName: " << entityName << " posY not valid!";
					return;
				}
				auto velocityX = entity["components"]["transform"]["velocity"]["x"];
				if (!velocityX.valid())
				{
					std::cerr << "entityName: " << entityName << " velocityX not valid!";
					return;
				}
				auto velocityY = entity["components"]["transform"]["velocity"]["y"];
				if (!velocityY.valid())
				{
					std::cerr << "entityName: " << entityName << " velocityY not valid!";
					return;
				}
				auto width = entity["components"]["transform"]["width"];
				if (!width.valid())
				{
					std::cerr << "entityName: " << entityName << " width not valid!";
					return;
				}
				auto height = entity["components"]["transform"]["height"];
				if (!height.valid())
				{
					std::cerr << "entityName: " << entityName << " height not valid!";
					return;
				}
				auto scale = entity["components"]["transform"]["scale"];
				if (!scale.valid())
				{
					std::cerr << "entityName: " << entityName << " scale not valid!";
					return;
				}

				newEntity.AddComponent<TransformComponent>(
					static_cast<int>(posX),
					static_cast<int>(posY),
					static_cast<int>(velocityX),
					static_cast<int>(velocityY),
					static_cast<int>(width),
					static_cast<int>(height),
					static_cast<int>(scale)
					);
			}

			//Add Sprite Component
			sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
			if (existsSpriteComponent != sol::nullopt) {
				std::string textureId = entity["components"]["sprite"]["textureAssetId"];
				bool isAnimated = entity["components"]["sprite"]["animated"];
				if (isAnimated) {
					newEntity.AddComponent<SpriteComponent>(
						textureId,
						static_cast<int>(entity["components"]["sprite"]["frameCount"]),
						static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
						static_cast<int>(entity["components"]["sprite"]["hasDirections"]),
						static_cast<int>(entity["components"]["sprite"]["fixed"])
						);
				}
				else {
					newEntity.AddComponent<SpriteComponent>(textureId, false);
				}
			}

			//Add Input Control Component
			sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
			if (existsInputComponent != sol::nullopt) {
				sol::optional<sol::table> existsKeyboardInputComponent = entity["component"]["keyboard"];
				if (existsKeyboardInputComponent != sol::nullopt) {

				}
			}
			
			//Add projectile emitter component
			sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"][""];

		}
		entityIndex++;
	}


	/*
	//Start including new assets to the assetmanager map
	assetmanager->AddTexture("tank-image", std::string("./assets/images/tank-tiger-right.png").c_str());
	assetmanager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetmanager->AddTexture("radar-image", std::string("./assets/images/radar-spritesheet.png").c_str());
	assetmanager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
	assetmanager->AddTexture("heliport-image", std::string("./assets/images/base-landing.png").c_str());
	assetmanager->AddTexture("projectile-image", std::string("./assets/images/bullet.png").c_str());
	assetmanager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

	map = new Map("jungle-tiletexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);


	//Start including entities and also components to them
	
	Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE_COLOR);

	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);


	Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
	tankEntity.AddComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
	tankEntity.AddComponent<SpriteComponent>("tank-image");
	tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

	TransformComponent* tankProjectile = tankEntity.GetComponent<TransformComponent>();

	Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
	projectile.AddComponent<TransformComponent>(tankProjectile->position.x+16 , tankProjectile->position.y + 16, 350, 0, 4, 4, 1);
	projectile.AddComponent<SpriteComponent>("projectile-image");
	projectile.AddComponent<ColliderComponent>("PROJECTILE", 150 + 16, 495 + 16, 4, 4);
	projectile.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

	Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
	heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	heliport.AddComponent<SpriteComponent>("heliport-image");
	heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

	Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
	
	


	//SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
	*/

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
	//TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();
	
	//camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
	//camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

	//Clamping of camera
	if (mainPlayer) {
		TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
		camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
		camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

		camera.x = camera.x < 0 ? 0 : camera.x;
		camera.y = camera.y < 0 ? 0 : camera.y;
		camera.x = camera.x > camera.w ? camera.w : camera.x;
		camera.y = camera.y > camera.h ? camera.h : camera.y;
	}
}

void Game::CheckCollisions() {
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == CollisionType::PLAYER_PROJECTILE_COLLISION) {
		ProcessGameOver();
	}
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