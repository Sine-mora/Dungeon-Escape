#ifndef GAMEWINSTATE_H
#define GAMEWINSTATE_H

#include "IState.h"

class GameWinState : public IState
{
public:
	GameWinState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::GameWinState; }
};
#endif // !GAMEWINSTATE_H