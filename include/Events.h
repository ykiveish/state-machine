#pragma once

#include "IEvent.h"

class DataA : public IEventData {
public:
	std::string Name;
};
/**
* @brief Event A.
*/
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
/**
* @brief Event B.
*/
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
/**
* @brief Event C.
*/
class EventC : public IEvent {
public:
	void SetData (IEventData* data) {
		Data = data;
	}
};