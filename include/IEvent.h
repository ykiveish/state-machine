#pragma once

#include <string>
#include "IEventData.h"

/**
* @brief Interface for events.
*
* This class defines base event structure.
*/
class IEvent {
public:
	virtual ~IEvent () { delete Data; };
	/**
     * Attaching data to the event.
     *
	 * @param IEventData* pointer to attached event.
     */
	virtual void SetData (IEventData* data) = 0;

	IEventData*  	Data; /**< Attached data. */
	std::string		Name; /**< Name of the event. */
};
