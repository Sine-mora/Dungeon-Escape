#include "LoadLevelState.h"


LoadLevelState::LoadLevelState(StateMgr* ptrOwner) : IState(ptrOwner)
{
}

void LoadLevelState::Update(float fDeltaTime)
{
}

void LoadLevelState::OnEnter()
{
    if (LoadLevel(1))
    {
        m_ptrOwner->ChangeState(EState::GamePlayState);
    }
}

void LoadLevelState::OnExit()
{
	std::cout << "On Exit Load Level\n";
}


bool LoadLevelState::LoadLevel(int levelNumber) 
{
    try 
    {
        sol::state lua;
        lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

        std::string levelName = "Level" + std::to_string(levelNumber);


        lua.script_file("./assets/scripts/" + levelName + ".lua");


        ///////////////////////////////////////////////////////////////////////////
        // LOAD LIST OF ASSETS FROM LUA CONFIG FILE
        ///////////////////////////////////////////////////////////////////////////
        sol::table levelData = lua[levelName];
        if (!levelData.valid())
        {
            std::cerr << "lua[levelName: " << levelName << "] is not valid!";
            return false;
        }

        sol::table levelAssets = levelData["assets"];
        if (!levelAssets.valid())
        {
            std::cerr << "levelData[\"assets\"] is not valid!";
            return false;
        }

        unsigned int assetIndex = 0;
        while (true) {
            sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
            if (existsAssetIndexNode == sol::nullopt) {
                break;
            }
            else {
                sol::table asset = levelAssets[assetIndex];
                if (!asset.valid())
                {
                    std::cerr << "levelAssets[assetIndex: " << assetIndex << "] is not valid!";
                    return false;
                }

                std::string assetType = asset["type"];
                if (assetType.compare("texture") == 0) {
                    std::string assetId = asset["id"];
                    std::string assetFile = asset["file"];
                    assetManager->AddTexture(assetId, assetFile.c_str());
                }
                if (assetType.compare("font") == 0) {
                    std::string assetId = asset["id"];
                    std::string assetFile = asset["file"];
                    int fontSize = asset["fontSize"];
                    assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
                }
            }
            assetIndex++;
        }

        ///////////////////////////////////////////////////////////////////////////
        // LOAD MAP AND TILE INFORMATION FROM LUA CONFIG FILE
        ///////////////////////////////////////////////////////////////////////////
        sol::table levelMap = levelData["map"];
        if (!levelMap.valid())
        {
            std::cerr << "LevelData[\"map\"] is not valid!";
            return false;
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
        // LOAD ENTITIES AND COMPONENTS FROM LUA CONFIG FILE
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
                    return false;
                }

                std::string entityName = entity["name"];
                LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

                // Add new entity
                auto& newEntity(manager.AddEntity(entityName, entityLayerType));

                // Add Transform Component
                sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
                if (existsTransformComponent != sol::nullopt) {
                    newEntity.AddComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"]),
                        static_cast<int>(entity["components"]["transform"]["scale"])
                        );
                }

                // Add sprite component
                sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
                if (existsSpriteComponent != sol::nullopt) {
                    std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                    bool isAnimated = entity["components"]["sprite"]["animated"];
                    if (isAnimated) {
                        newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                            static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                            static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                            static_cast<bool>(entity["components"]["sprite"]["fixed"])
                            );
                    }
                    else {
                        newEntity.AddComponent<SpriteComponent>(textureId, false);
                    }
                }

                // Add input control component
                sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
                if (existsInputComponent != sol::nullopt) {
                    sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
                    if (existsKeyboardInputComponent != sol::nullopt) {
                        std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                        std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                        std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                        std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                        std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                        newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                    }
                }

                // Add collider component
                sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
                if (existsColliderComponent != sol::nullopt) {
                    std::string colliderTag = entity["components"]["collider"]["tag"];
                    newEntity.AddComponent<ColliderComponent>(
                        colliderTag,
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"])
                        );
                }

                // Add projectile emitter component
                sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
                if (existsProjectileEmitterComponent != sol::nullopt) {
                    int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                    int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                    int parentEntityWidth = entity["components"]["transform"]["width"];
                    int parentEntityHeight = entity["components"]["transform"]["height"];
                    int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                    int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                    int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                    int projectileRange = entity["components"]["projectileEmitter"]["range"];
                    int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                    bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                    std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                    Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
                    projectile.AddComponent<TransformComponent>(
                        parentEntityXPos + (parentEntityWidth / 2),
                        parentEntityYPos + (parentEntityHeight / 2),
                        0,
                        0,
                        projectileWidth,
                        projectileHeight,
                        1
                        );
                    projectile.AddComponent<SpriteComponent>(textureAssetId);
                    projectile.AddComponent<ProjectileEmitterComponent>(
                        projectileSpeed,
                        projectileAngle,
                        projectileRange,
                        projectileShouldLoop
                        );
                    projectile.AddComponent<ColliderComponent>(
                        "PROJECTILE",
                        parentEntityXPos,
                        parentEntityYPos,
                        projectileWidth,
                        projectileHeight
                        );
                }
            }
            entityIndex++;
        }

        mainPlayer = manager.GetEntityByName("player");

    }
    catch (const sol::error& e)
    {
        std::cerr << "Failed to load level. e.what(): " << e.what() << "\n";
        return false;
    }
    
    return true;
}