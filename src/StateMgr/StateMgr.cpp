#include <map>
#include "StateMgr.h"


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

}

void StateMgr::RegisterState(IState* ptrState)
{
	if (ptrState)
	{
		m_mapStates.insert(std::make_pair(ptrState->GetName(), std::move(ptrState)));
	}
}
