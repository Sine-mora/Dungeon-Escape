#ifndef LOADLEVELSTATE_H
#define LOADLEVELSTATE_H

#include "IState.h"

class LoadLevelState : public IState
{
public:
	LoadLevelState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::LoadLevelState; }
};
#endif // !LOADLEVELSTATE_H