#ifndef STATEMNGR_H
#define STATEMNGR_H

#include <map>
#include <iostream>
#include "IState.h"
#include "EState.h"


class StateMgr
{
public:
	StateMgr();
	~StateMgr();

	void Update(float fDeltaTime);
	void ChangeState(const EState stateName);

	/* Add a new State to the map */
	void RegisterState(IState* ptrState);

	IState* GetCurrentState() const { return m_ptrCurrentState; }

private:
	/* Maps the name of the state to its  instance */
	std::map<EState, std::unique_ptr<IState>> m_mapStates;

	/* Current state we're in */
	IState* m_ptrCurrentState;
};
#endif // !STATEMNGR_H