#pragma once
#include "Body.h"
class Player: public Body
{
public:
	void drawBody() {
		cout << "#";
	}
};

