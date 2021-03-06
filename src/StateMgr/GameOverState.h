#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "IState.h"

class GameOverState : public IState
{
public:
	GameOverState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::GameOverState; }
};
#endif // !GAMEOVERSTATE_H