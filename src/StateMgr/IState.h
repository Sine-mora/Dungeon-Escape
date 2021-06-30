#ifndef ISTATES_H
#define ISTATES_H

#include "EState.h"

class StateMgr; //Forward declaration to StateMgr

class IState
{
public:
	IState(StateMgr* ptrOwner) : m_ptrOwner(ptrOwner)
	{}
	virtual ~IState() = default;
	
	//TODO: Add Draw(), Add Render()

	/* State-specific behavior */
	/* Update the state */
	virtual void Update(float fDeltaTime) = 0;
	/* Any entry transition code */
	virtual void OnEnter() = 0;
	/* Any exit transition code */
	virtual void OnExit() = 0;
	/* Getter for string name of this state */
	virtual EState GetName() const = 0;

protected:
	/* The Player this state belongs to */
	StateMgr* m_ptrOwner;
};
#endif // !ISTATES_H