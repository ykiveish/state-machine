#pragma once

#include "IEvent.h"

class DataA : public IEventData {
public:
	std::string Name;
};

class EventA : public IEvent {
public:
	void SetData (IEventData* data) {
		Data = data;
	}
};

class DataB : public IEventData {
public:
	std::string Name;
};

class EventB : public IEvent {
public:
	void SetData (IEventData* data) {
		Data = data;
	}
};

class DataC : public IEventData {
public:
	std::string Name;
};

class EventC : public IEvent {
public:
	void SetData (IEventData* data) {
		Data = data;
	}
};