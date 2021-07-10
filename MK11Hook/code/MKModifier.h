#pragma once
#include "MKCharacter.h"
#include "mk10utils.h"

class BaseModifier {
public:
	char data[96] = {};
};

class TagModifier : public BaseModifier {
public:
	TagModifier(const char* character);
	void Activate(int64 info);
};


class MKModifier {
public:
	void ActivateModifier(BaseModifier* modifier, MKCharacter* obj);
};



