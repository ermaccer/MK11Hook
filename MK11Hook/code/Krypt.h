#pragma once
#include "MKObject.h"

class Krypt {
public:
	MKObject* GetKryptPlayer(int value);
	void	  BuildPlayer();
};

Krypt* GetKrypt();