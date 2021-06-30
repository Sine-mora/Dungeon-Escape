#ifndef LOADLEVELSTATE_H
#define LOADLEVELSTATE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "IState.h"
#include "sol.hpp"
#include "Component.h"
#include "EntityManager.h"
#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include <iostream>
#include <Renderer/Renderer2D.h>

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "KeyboardControlComponent.h"
#include "TextLabelComponent.h"
#include "ProjectileEmitterComponent.h"

#include "StateMgr.h"

class AssetManager;

class LoadLevelState : public IState
{
public:
	LoadLevelState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::LoadLevelState; }
	
	bool LoadLevel(int levelNumber);
	static AssetManager* assetManager;

private:

	Map* map;
	EntityManager manager;

};
#endif // !LOADLEVELSTATE_H