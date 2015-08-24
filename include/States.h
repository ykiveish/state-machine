#pragma once

#include "IState.h"
#include <iostream>

class Idle : public IState {
public:
	Idle () {
		State = IDLE;
	}

	void HandleEvent () {
		std::cout << "Idle::HandleEvent" << std::endl;
	}
};

class StateA : public IState {
public:
	StateA () {
		State = STATE_A;
	}

	void HandleEvent () {
		std::cout << "StateA::HandleEvent" << std::endl;
	}
};

class StateB : public IState {
public:
	StateB () {
		State = STATE_B;
	}

	void HandleEvent () {
		std::cout << "StateB::HandleEvent" << std::endl;
	}
};

class StateC : public IState {
public:
	StateC () {
		State = STATE_C;
	}

	void HandleEvent () {
		std::cout << "StateC::HandleEvent" << std::endl;
	}
};