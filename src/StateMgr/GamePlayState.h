#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include <Renderer/Renderer2D.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "sol.hpp"
#include "IState.h"
#include "StateMgr.h"
#include "Game.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "KeyboardControlComponent.h"
#include "TextLabelComponent.h"
#include "ProjectileEmitterComponent.h"

class AssetManager;

class GamePlayState : public IState
{
public:
	GamePlayState(StateMgr* ptrOwner);
	~GamePlayState();

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::GamePlayState; }

	void ProcessNextLevel(int levelNumber);
	void ProcessGameOver();
	void HandleCameraMovement();
	void CheckCollisions();


private:
	int m_iTicksLastFrame = 0;
	bool m_isRunning;
	float m_fCountdown;
	StateMgr m_stateMgr;
	EntityManager manager;
	Entity* m_mainPlayer = NULL;
	SDL_Rect camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
};

#endif // !GAMEPLAYSTATE_H