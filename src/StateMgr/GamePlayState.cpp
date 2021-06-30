#include "GamePlayState.h"

GamePlayState::GamePlayState(StateMgr* ptrOwner): IState (ptrOwner)
{

}

void GamePlayState::Update(float fDeltaTime)
{

    // Waste some time / sleep until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - m_iTicksLastFrame);

    // Only sleep if we are too fast
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - m_iTicksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    m_iTicksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
    m_stateMgr.Update(deltaTime);

    HandleCameraMovement();
    CheckCollisions();
}



void GamePlayState::OnEnter()
{
	std::cout << "On Enter Gameplay State\n";
    m_mainPlayer = manager.GetEntityByName("player");
}

void GamePlayState::OnExit()
{
	std::cout << "On Exit Gameplay State\n";
    m_mainPlayer = NULL;
}

void GamePlayState::HandleCameraMovement() {
    if (m_mainPlayer) {
        TransformComponent* mainPlayerTransform = m_mainPlayer->GetComponent<TransformComponent>();
        const auto& screenSize = K9::Renderer2D::Ref().GetScreenSize();
        camera.x = mainPlayerTransform->position.x - (screenSize.w / 2);
        camera.y = mainPlayerTransform->position.y - (screenSize.h / 2);

        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}

void GamePlayState::CheckCollisions() {
    CollisionType collisionType = manager.CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_PROJECTILE_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessNextLevel(1);
    }
}

void GamePlayState::ProcessNextLevel(int levelNumber) {
    std::cout << "Next Level" << std::endl;
    m_isRunning = false;
}

void GamePlayState::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    m_isRunning = false;
}
