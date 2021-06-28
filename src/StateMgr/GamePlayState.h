#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "IState.h"



class GamePlayState : public IState
{
public:
	GamePlayState(StateMgr* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::GamePlayState; }
private:

	float m_fCountdown;
};

#endif // !GAMEPLAYSTATE_H