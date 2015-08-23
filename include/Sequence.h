#pragma once

#include <iostream>
#include <queue>

class Sequence {
public:
	Sequence (int ** sequence, int length);
	~Sequence ();

	void UpdateItems (int item);
	bool GetStatus ();
private:
	int 			m_SequenceLength;
	std::queue<int> m_SequenceWindow;
};