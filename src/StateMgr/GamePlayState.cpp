#include <iostream>
#include "GamePlayState.h"
#include "StateMgr.h"

GamePlayState::GamePlayState(StateMgr* ptrOwner): IState (ptrOwner)
{

}

void GamePlayState::Update(float fDeltaTime)
{
	m_fCountdown = m_fCountdown - fDeltaTime;

	std::cout << m_fCountdown<<"\n";

	if (m_fCountdown <= 0)
	{
		m_ptrOwner->ChangeState(EState::LoadLevelState);
	}

}

void GamePlayState::OnEnter()
{

	m_fCountdown = 5;

	std::cout << "On Enter Gameplay State\n";

}

void GamePlayState::OnExit()
{
	std::cout << "On Exit Gameplay State\n";
}