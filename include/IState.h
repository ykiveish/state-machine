#pragma once

class IState {
public:
	virtual void HandleEvent () = 0;
};
