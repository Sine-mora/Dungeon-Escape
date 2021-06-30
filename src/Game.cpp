#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "KeyboardControlComponent.h"
#include "TextLabelComponent.h"
#include "ProjectileEmitterComponent.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include <optional>
#include <Renderer/Renderer2D.h>

#include "StateMgr/GamePlayState.h"
#include "StateMgr/LoadLevelState.h"



EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Entity* mainPlayer = NULL;

std::optional;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return this->isRunning;
}

bool Game::Initialize(int width, int height) {
    if (!K9::Renderer2D::Ref().Init("Title", width, height))
    {
        std::cerr << "Game::Initialize Error! Failed to init K9::Renderer2D\n";
        return false;
    }
    m_stateMgr.RegisterState(new GamePlayState(&m_stateMgr));
    m_stateMgr.RegisterState(new LoadLevelState(&m_stateMgr));

    m_stateMgr.ChangeState(EState::LoadLevelState);

    isRunning = true;
    return true;
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
            }
            break;
        }
        default: {
            break;
        }
    }

    K9::Renderer2D::Ref().HandleEvent(event);
}

void Game::Update() 
{
    // Waste some time / sleep until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    // Only sleep if we are too fast
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
    m_stateMgr.Update(deltaTime);
}

void Game::Render() 
{
    auto& rend = K9::Renderer2D::Ref();
    rend.BeginFrame();

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    K9::Renderer2D::Ref().BeginImGUIFrame();
    ImGui::ShowDemoWindow(&isRunning);
    ImGui::ShowAboutWindow(&isRunning);
    



    K9::Renderer2D::Ref().EndImGUIFrame();


    rend.EndFrame();
}

void Game::Destroy() {
    K9::Renderer2D::Ref().Shutdown();
}
