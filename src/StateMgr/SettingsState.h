#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "IState.h"

class SettingsState : public IState
{
public:
	SettingsState(StateMgr* ptrOwner);
	~SettingsState();

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual EState GetName() const override { return EState::SettingsState; }
};
#endif // !SETTINGSSTATE_H