#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "IState.h"

class MainMenuState : public IState
{
public:
	MainMenuState(StateMgr* ptrOwner);
	~MainMenuState();

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::MainMenuState; }
};

#endif // !MAINMENUSTATE_H