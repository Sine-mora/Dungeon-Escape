#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize) {
	this->textureId = textureId;
	this->scale = scale;
	this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	//TODO read the map tile definitions from the .map file
	std::fstream mapFile;
	mapFile.open(filePath);

	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			char ch;
			mapFile.get(ch);
			int sourceRectY = atoi(&ch) * tileSize;
			mapFile.get(ch);
			int sourceRectX = atoi(&ch) * tileSize;
			AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y) {
	//TODO Add a new tile entity in the game scene
	Entity& newTile(manager.AddEntity("Tile"));
	newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}