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

		/*
		 * Basicaly should have socket implementation for remote requesrs.
		 */

		usleep (10000);
	}

	return NULL;
}

StateMachine::StateMachine (onMatchingCallback cb) {
	// Initating the states repo.
	m_StateDB[typeid(Idle).hash_code()] 	= new Idle ();
	m_StateDB[typeid(StateA).hash_code()] 	= new StateA ();
	m_StateDB[typeid(StateB).hash_code()] 	= new StateB ();
	m_StateDB[typeid(StateC).hash_code()] 	= new StateC ();

	// Setting the current status.
	m_CurrentState = m_StateDB[typeid(Idle).hash_code()];
	// Letting the thread loop to work.
	IsWorking = true;

	// Loading last state (if any)
	LoadLastStateFS ();
	// Callback for matching event.
	m_MachingCB = cb;

	// Starting the event.
	int error = pthread_create (&m_Worker, NULL, StateMachineWorker, this);
	if (error) {
		m_StateDB.clear ();
	}
}

StateMachine::~StateMachine () {
	m_StateDB.clear ();
}

void
StateMachine::StopMachine () {
	SaveLastStateFS ();
	IsWorking = false;
	pthread_cancel (m_Worker);
}

void
StateMachine::SetEvent (IEvent* event) {
	// Leting engine (thread) know about new event arrived.
	IsNewEvent = true;
	// Pointing to the new event.
	NewEvent = event;
}

void
StateMachine::EventHandler (IEvent* event) {
	const std::type_info& 	eventType 			= typeid(*event);
	std::string 			eventTypeName 		= eventType.name();
	IState* 				state 				= NULL;

	if (!eventTypeName.compare(typeid(EventA).name())) {
		/* 
		 * Logic for EventA will be here. We can check the current state 
		 * and according to the state change the state machine.
		 */
		// Getting the instance of the state.
		state = m_StateDB[typeid(StateA).hash_code()];
		if (state != NULL) {
			// casting to the correct event and calling for the handler.
			dynamic_cast<StateA*>(state)->HandleEvent ();
			// Setting the current state.
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	} else if (!eventTypeName.compare(typeid(EventB).name())) {
		/* 
		 * Logic for EventB will be here. We can check the current state 
		 * and according to the state change the state machine.
		 */
		state = m_StateDB[typeid(StateB).hash_code()];
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
		state = m_StateDB[typeid(StateC).hash_code()];
		if (state != NULL) {
			dynamic_cast<StateC*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	} else {
		state = m_StateDB[typeid(Idle).hash_code()];
		if (state != NULL) {
			dynamic_cast<Idle*>(state)->HandleEvent ();
			m_CurrentState = state;
		} else {
			std::cout << "ERROR (Can't cast NULL)" << std::endl;
		}
	}

	// If state was real, lets update and check for sequences.
	if (state != NULL) {
		for (size_t i = 0; i < m_Sequences.size(); i++) {
			// Fetching sequence from the list.
			Sequence* seq = &(m_Sequences.at(i));
			// Adding item.
			seq->UpdateItems (state->State);
			// Checking for matching.
			std::vector<int> info;
			if (seq->GetStatus (info) == true) {
				// Generating messahe.
				Message* msg = new Message ();
				msg->Name = seq->Name;
				msg->ListOfAny = info;
				// Firing the evnt.
				m_MachingCB (msg);
			}
		}
	}
	
	// Deleting the event.
	delete event;
}

void
StateMachine::AddSequence (Sequence& seq) {
	seq.UpdateItems (m_CurrentState->State);
	m_Sequences.push_back (seq);
}

void
StateMachine::SaveLastStateFS () {
	std::ofstream file;
	file.open ("last-state.save");
	file << m_CurrentState->State;
	file.close();
}

void
StateMachine::LoadLastStateFS () {
	std::string data;
	std::ifstream file ("last-state.save");
	if (file.is_open()) {
		while (getline (file, data)) { }

		switch ((STATE)(std::stoi(data))) {
			case IDLE:
				m_CurrentState = m_StateDB[typeid(Idle).hash_code()];
			break;
			case STATE_A:
				m_CurrentState = m_StateDB[typeid(StateA).hash_code()];
			break;
			case STATE_B:
				m_CurrentState = m_StateDB[typeid(StateB).hash_code()];
			break;
			case STATE_C:
				m_CurrentState = m_StateDB[typeid(StateC).hash_code()];
			break;
			default:
				m_CurrentState = m_StateDB[typeid(Idle).hash_code()];
			break;
		}

		file.close ();
	}

	std::cout << data << std::endl;
}

std::string
StateMachine::StateToString (STATE state) {
	switch (state) {
		case IDLE:
			return "IDLE";
		case STATE_A:
			return "STATE_A";
		case STATE_B:
			return "STATE_B";
		case STATE_C:
			return "STATE_C";
		default:
			return "UNKNOWN";
	}
}

/*
 * PRIVATE
 */
