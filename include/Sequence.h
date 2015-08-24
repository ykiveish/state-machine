#pragma once

#include <iostream>
#include <queue>
#include "IState.h"

/**
* @brief Class for sequence.
*
* This class mennaging the sequence identification.
*/
class Sequence {
public:
	/**
     * Constructor.
     *
	 * @param sequence[] sequence (array) of numbers.
	 * @param length length of the array.
	 * @param name is name of the sequence.
     */
	Sequence (int sequence[], int length, std::string name);
	~Sequence ();

	/**
     * Updating the sercular buffer with new data.
     *
	 * @param item simple intger number, sequence id.
     */
	void UpdateItems (int item);
	/**
     * Checking for the matching.
     *
     * @param info is reference to aditional data.
	 * @return status of matchinf true or false.
     */
	bool GetStatus (std::vector<int>& info);

	std::string Name; /**< Sequence name. */
private:
	unsigned		  m_SequenceLength;	/**< Sequence array length. */
	std::vector<int>  m_SequenceWindow;	/**< Circular buffer. */
	std::vector<int>  m_Sequence;		/**< The sequence. */
	bool 			  m_IsAnyEvent;		/**< Alerting on sequence have ANY state item. */
};