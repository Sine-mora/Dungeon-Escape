#include <map>
#include "StateMgr.h"
#include <iostream>

StateMgr::StateMgr(): m_mapStates{}, m_ptrCurrentState{nullptr}
{
}

StateMgr::~StateMgr()
{
}

void StateMgr::Update(float fDeltaTime)
{
	if (m_ptrCurrentState != NULL) 
	{
		m_ptrCurrentState->Update(fDeltaTime);
	}

}

void StateMgr::ChangeState(const EState stateName)
{
	if (m_ptrCurrentState)
	{
		m_ptrCurrentState->OnExit();
	}
	// Find the stateName from the map
	auto stateIt = m_mapStates.find(stateName);
	if (stateIt != m_mapStates.end())
	{
		/* We're entering the new state */
		m_ptrCurrentState = stateIt->second.get();
		m_ptrCurrentState->OnEnter();
		
	}
	else
	{
		std::cout << "Could not find AIState in m_mapOfStates!Setting m_ptrCurrentState to nullptr!";
		m_ptrCurrentState = nullptr;
	}
}

void StateMgr::RegisterState(IState* ptrState)
{
	if (ptrState)
	{
		m_mapStates.insert(std::make_pair(ptrState->GetName(), std::move(ptrState)));
	}
}
