#include "LoadLevelState.h"
#include "GamePlayState.h"
#include "StateMgr.h"
#include <iostream>

LoadLevelState::LoadLevelState(StateMgr* ptrOwner) : IState(ptrOwner)
{
}

void LoadLevelState::Update(float fDeltaTime)
{
	m_fCountdown = m_fCountdown - fDeltaTime;
	std::cout << m_fCountdown << "\n";
	if (m_fCountdown <= 0)
	{
		m_ptrOwner->ChangeState(EState::GamePlayState);
	}

}

void LoadLevelState::OnEnter()
{
	m_fCountdown = 10;
	std::cout << "On Enter Load Level\n";
}

void LoadLevelState::OnExit()
{
	std::cout << "On Exit Load Level\n";
}
