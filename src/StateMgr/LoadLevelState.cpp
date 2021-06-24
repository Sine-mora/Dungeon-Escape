#include "LoadLevelState.h"
#include "GamePlayState.h"
#include <iostream>

void LoadLevelState::Update(float fDeltaTime)
{
	for (int i = 0; i <= 10; i++)
	{
		std::cout << " Load level State: " << i << " ";
	}

}

void LoadLevelState::OnEnter()
{
	float fDeltaTime;
	std::cout << " Load Level State On Enter:\n";
	Update( fDeltaTime);
	OnExit();
}

void LoadLevelState::OnExit()
{

}
