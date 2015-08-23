#pragma once

#include <string>
#include "IEventData.h"

enum STATE {
	STATE_A = 0,
	STATE_B = 1,
	STATE_C = 2
};

class IEvent {
public:
	virtual ~IEvent () { delete Data; };
	virtual void SetData (IEventData* data) = 0;

	IEventData*  	Data;
	std::string		Name;
};
