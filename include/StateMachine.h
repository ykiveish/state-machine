#pragma once

#include "Events.h"
#include "States.h"
#include "Sequence.h"
#include <map>
#include <iostream>
#include <string.h>
#include <fstream>
#include <pthread.h>

/**
 * Message recieved together with a callback on matching 
 * sequence.
 */
struct Message {
    std::string Name; /**< Name of sequence */
    std::vector<int> ListOfAny; /**< More info. */
};

/**
 * Callback for matching sequence.
 */
typedef void (* onMatchingCallback) (
    Message * data /**< Data info */
);

/**
* @brief Simple state machine engine.
*
* This class define all supported methods in statemachine.
*/
class StateMachine {
public:
	/**
     * Constructor.
     *
	 * @param cb is a callback for matching sequence.
     */
	StateMachine (onMatchingCallback cb);
	~StateMachine ();

	/**
     * Stoping the machine and the inner thread.
     */
	void StopMachine ();
	/**
     * Announcing the new evwnt arrived.
     *
     * @param IEvent* pointer arrived event structure.
     */
	void SetEvent (IEvent* event);
	/**
     * Handling the arrived event.
     * Redirect to correct state for handling.
     *
     * @param IEvent* pointer arrived event structure.
     */
	void EventHandler (IEvent* event);
	/**
     * Adding sequnce structure to the engine. This sequence
     * will be monitor inside the engine.
     *
     * @param Sequence& reference to new sequence.
     */
	void AddSequence (Sequence& seq);
	/**
     * Saving the last state ID to the file.
     */
	void SaveLastStateFS ();
	/**
     * Loading the last state ID to the engine.
     */
	void LoadLastStateFS ();
	/**
     * Convert STATE type to string.
     *
     * @param state refering to STATE type.
     */
	static std::string StateToString (STATE state);
	
	bool 		IsWorking;   /**< Setting the inner thread loop. */
	bool		IsNewEvent;  /**< New event arrived. */
	IEvent*		NewEvent;    /**< Pointer to the new event. */

private:
	typedef std::map<size_t, IState*> 	StateMap;

	IState* 				m_CurrentState; /**< Current state of the engine */
	StateMap 				m_StateDB;		/**< Hash map of available states. */
	pthread_t 				m_Worker;		/**< Thread for the future network event injection */
	std::vector<Sequence> 	m_Sequences;	/**< List of sequences to monitor. */
	onMatchingCallback		m_MachingCB;	/**< Callback for matching event. */
};