#pragma once

#include "Events.h"
#include "States.h"
#include <map>
#include <pthread.h>

class StateMachine {
public:
	StateMachine ();
	~StateMachine ();

	void SetEvent (IEvent* event);
	void EventHandler (IEvent* event);
	
	bool 		IsWorking;
	bool		IsNewEvent;
	IEvent*		NewEvent;

private:
	typedef std::map<size_t, IState*> 	StateMap;

	IState* 	m_CurrentState;
	StateMap 	m_StateDB;
	pthread_t 	m_Worker;
};