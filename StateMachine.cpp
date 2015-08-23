#include "StateMachine.h"
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <time.h>
#include <unistd.h>

/*
 * This thread also can be used for networking/IPC events request.
 */
void *
StateMachineWorker (void * args) {
	StateMachine* obj = (StateMachine *)args;

	while (obj->IsWorking) {
		if (obj->IsNewEvent) {
			obj->EventHandler (obj->NewEvent);
			obj->IsNewEvent = false;
		}

		usleep (10000);
	}

	return NULL;
}

StateMachine::StateMachine () {
	m_StateDB[typeid(Idle).hash_code()] 	= new Idle ();
	m_StateDB[typeid(StateA).hash_code()] 	= new StateA ();
	m_StateDB[typeid(StateB).hash_code()] 	= new StateB ();
	m_StateDB[typeid(StateC).hash_code()] 	= new StateC ();

	m_CurrentState = m_StateDB[typeid(Idle).hash_code()];
	IsWorking = true;

	int error = pthread_create (&m_Worker, NULL, StateMachineWorker, this);
	if (error) {
		m_StateDB.clear ();
	}
}

StateMachine::~StateMachine () {
	m_StateDB.clear ();
}

void
StateMachine::SetEvent (IEvent* event) {
	IsNewEvent = true;
	NewEvent = event;
}

void
StateMachine::EventHandler (IEvent* event) {
	const std::type_info& 	eventType 			= typeid(*event);
	std::string 			eventTypeName 		= eventType.name();
	
	if (!eventTypeName.compare(typeid(EventA).name())) {
		/* 
		 * Logic for EventA will be here. We can check the current state 
		 * and according to the state change the state machine.
		 */
		IState* state = m_StateDB[typeid(StateA).hash_code()];
		if (state != NULL) {
			dynamic_cast<StateA*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	} else if (!eventTypeName.compare(typeid(EventB).name())) {
		/* 
		 * Logic for EventB will be here. We can check the current state 
		 * and according to the state change the state machine.
		 */
		IState* state = m_StateDB[typeid(StateB).hash_code()];
		if (state != NULL) {
			dynamic_cast<StateB*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	} else if (!eventTypeName.compare(typeid(EventC).name())) {
		/* 
		 * Logic for EventC will be here. We can check the current state 
		 * and according to the state change the state machine.
		 */
		IState* state = m_StateDB[typeid(StateC).hash_code()];
		if (state != NULL) {
			dynamic_cast<StateC*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	} else {
		IState* state = m_StateDB[typeid(Idle).hash_code()];
		if (state != NULL) {
			dynamic_cast<Idle*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	}

	delete event;
}

/*
 * PRIVATE
 */
