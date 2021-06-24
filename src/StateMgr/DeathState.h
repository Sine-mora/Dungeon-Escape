#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "IState.h"

class DeathState : public IState
{
public:
	DeathState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::DeathState; }
};
#endif // !DEATHSTATE_H