#include "Sequence.h"
#include <iostream>

Sequence::Sequence (int sequence[], int length, std::string name) {
	for (int i = 0; i < length; i++) {
		m_Sequence.push_back (sequence[i]);
		// If ANY type exist, let know the sequence.
		if (sequence[i] == ANY) {
			m_IsAnyEvent = true;
		}
	}

	m_SequenceLength = length;
	Name 			 = name;
}

Sequence::~Sequence () {
	m_Sequence.clear();
}

void
Sequence::UpdateItems (int item) {
	/* 
	 * If the ammount of event reached the circular buffer size 
	 * we starting to delete the head.
	 */ 
	if (m_SequenceWindow.size() == m_SequenceLength) {
		m_SequenceWindow.erase (m_SequenceWindow.begin());
	}

	// Update the tail of the buffer.
	m_SequenceWindow.push_back (item);

	for (unsigned i = 0; i < m_SequenceWindow.size(); i++) {
		std::cout << m_SequenceWindow.at(i) << " ";
	} std::cout << std::endl;
}

bool
Sequence::GetStatus (std::vector<int>& info) {
	/* 
	 * If the ammount of event reached the circular buffer size 
	 * we starting to search for the matching.
	 */ 
	if (m_SequenceWindow.size() == m_SequenceLength) {
		// If no ANY item in the sequence, lets do the simple comparison.
		if (m_IsAnyEvent == false) {
			return std::equal (m_SequenceWindow.begin(), m_SequenceWindow.end(), m_Sequence.begin());
		}

		// Comparison with ANY type.
		int item = 99;
		for (unsigned i = 0; i < m_SequenceWindow.size(); i++) {
			item = m_SequenceWindow.at(i);

			if (m_Sequence.at(i) == ANY) {
				info.push_back (item);
			}

			if (item != m_Sequence.at(i) && m_Sequence.at(i) != ANY) {
				return false;
			}
		}

		return true;
	}

	return false;
}