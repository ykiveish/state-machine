#pragma once

#include "IState.h"
#include <iostream>

class Idle : public IState {
public:
	void HandleEvent () {
		std::cout << "Idle::HandleEvent" << std::endl;
	}
};

class StateA : public IState {
public:
	void HandleEvent () {
		std::cout << "StateA::HandleEvent" << std::endl;
	}
};

class StateB : public IState {
public:
	void HandleEvent () {
		std::cout << "StateB::HandleEvent" << std::endl;
	}
};

class StateC : public IState {
public:
	void HandleEvent () {
		std::cout << "StateC::HandleEvent" << std::endl;
	}
};