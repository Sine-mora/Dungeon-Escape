#ifndef GAMEPAUSEDSTATE_H
#define GAMEPAUSEDSTATE_H

#include "IState.h"

class GamePausedState : public IState
{
public:
	GamePausedState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::GamePausedState; }
};

#endif // !GAMEPAUSEDSTATE_H