#pragma once

/**
 * State machine state types
 */
enum STATE {
	STATE_A = 0,  	/**< State A */
	STATE_B = 1,	/**< State B */
	STATE_C = 2,	/**< State C */
	IDLE    = 98,	/**< State IDLE */
	ANY     = 99	/**< State ANY|UNDEFINED */
};

/**
* @brief Interface for States.
*
* This class defines base state structure.
*/
class IState {
public:
	/**
     * Handeling the event when arriving to the state.
     *
	 * @param IEventData* pointer to attached event.
     */
	virtual void HandleEvent () = 0;

	STATE State; /**< Type of state. */
};
