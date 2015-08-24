#include "StateMachine.h"
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>

STATE TEST[] = {
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A
};
int TEST_INDEX = 0;

void CreateA (IEvent ** event);
void CreateB (IEvent ** event);
void CreateC (IEvent ** event);

STATE SequenceOne[] = {
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A, STATE_A
};

STATE SequenceTwo[] = {
	STATE_A, ANY, STATE_C, ANY
};

StateMachine* engine = NULL;
bool amWorking = true;

void
sig_handler(int signo)
{
    if (signo == SIGINT) {
        std::cout << "GOT SOFT INT CLOSE NICELY ..." << std::endl;
        engine->StopMachine ();
        amWorking = false;
    }
}

void
matchingHandler (Message* msg) {
	std::cout << msg->Name << std::endl;
	for (unsigned i = 0; i < msg->ListOfAny.size(); i++) {
		std::cout << StateMachine::StateToString((STATE)msg->ListOfAny.at(i)) << " " << std::endl;
	}

	delete msg;
}

int
main (int argc, char ** argv) {
	// Creating the instatnce of new machine.
	engine = new StateMachine (matchingHandler);
	IEvent* event = NULL;

	// Creating two sequences to monitor.
	Sequence seqOne = Sequence((int *)SequenceOne, 6, "FIRST");
	Sequence seqTwo = Sequence((int *)SequenceTwo, 4, "ANY");
	// Adding these two sequences to the engine.
	engine->AddSequence(seqOne);
	engine->AddSequence(seqTwo);

	// Handaling the user kill application signal, for clean application close.
	signal(SIGINT, sig_handler);
	// Main loop.
	while (amWorking) {
		switch (TEST[TEST_INDEX]) {
			case STATE_A:
				CreateA (&event);
			break;
			case STATE_B:
				CreateB (&event);
			break;
			case STATE_C:
				CreateC (&event);
			break;
			default:
			break;
		}
		
		if (event != NULL) {
			// Announcing the event.
			engine->SetEvent (event);
		}
		
		// Round test.
		if ((++TEST_INDEX) == 20) {
			TEST_INDEX = 0;
		}
		
		// Fetching event from test repo each one second.
		usleep (1000000 * 1);
	}

	// Resource free.
	delete engine;
	
	std::cout << "Exit 'state-test'" << std::endl;
	return 0;
}

void
CreateA (IEvent ** event) {
	*event = new EventA ();
	// Attached event's data.
	(*event)->Data = new DataA ();
}

void
CreateB (IEvent ** event) {
	*event = new EventB ();
	// Attached event's data.
	(*event)->Data = new DataB ();
}

void
CreateC (IEvent ** event) {
	*event = new EventC ();
	// Attached event's data.
	(*event)->Data = new DataC ();
}
