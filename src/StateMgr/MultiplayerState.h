#ifndef MULTIPLAYERSTATE_H
#define MULTIPLAYERSTATE_H

#include "IState.h"

class MultiplayerState : public IState
{
public:
	MultiplayerState(StateMgr* ptrOwner);
	~MultiplayerState();

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::MultiplayerState; }
};

#endif // !MULTIPLAYERSTATE_H