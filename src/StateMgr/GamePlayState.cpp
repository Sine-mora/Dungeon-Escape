#include "GamePlayState.h"
#include "LoadLevelState.h"
#include <iostream>

void GamePlayState::Update(float fDeltaTime)
{
	for (int i = 0; i <= 10; i++)
	{
		std::cout << " Gameplay State: " << i << " ";
	}
}

void GamePlayState::OnEnter()
{
	float fDeltaTime;
	std::cout << " Gameplay State On Enter:\n";
	Update(fDeltaTime);

	OnExit();
}

void GamePlayState::OnExit()
{
}