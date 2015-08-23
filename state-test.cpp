#include "StateMachine.h"
#include <iostream>
#include <time.h>
#include <unistd.h>

STATE TEST_ONE[20] = {
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A,
	STATE_A, STATE_B, STATE_C, STATE_A, STATE_A
};
int TEST_ONE_INDEX = 0;

void CreateA (IEvent ** event);
void CreateB (IEvent ** event);
void CreateC (IEvent ** event);

int
main (int argc, char ** argv) {
	StateMachine* engine = new StateMachine ();
	IEvent* event = NULL;

	while (true) {
		switch (TEST_ONE[TEST_ONE_INDEX]) {
			case STATE_A:
				CreateA (&event);
			break;
			case STATE_B:
				CreateB (&event);
			break;
			case STATE_C:
				CreateC (&event);
			break;
		}

		if (event != NULL) {
			engine->SetEvent (event);
		}

		if ((++TEST_ONE_INDEX) == 20) {
			TEST_ONE_INDEX = 0;
		}
		
		usleep (1000000 * 1);
	}

	delete engine;
	
	std::cout << "Exit 'cortica-test'" << std::endl;
	return 0;
}

void
CreateA (IEvent ** event) {
	*event = new EventA ();
	(*event)->Data = new DataA ();
}

void
CreateB (IEvent ** event) {
	*event = new EventB ();
	(*event)->Data = new DataB ();
}

void
CreateC (IEvent ** event) {
	*event = new EventC ();
	(*event)->Data = new DataC ();
}
