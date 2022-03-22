#pragma once
#include "MKCharacter.h"
#include "mk10utils.h"
#include "PlayerInfo.h"

class BaseModifier {
public:
	char data[96] = {};
};

class TagAssistModifierObject {
public:
	void Activate(MKCharacter* obj);
};

class TagAssistModifier : public BaseModifier {
public:
	TagAssistModifier(const char* character);
	void Activate(PlayerInfo* info);
	TagAssistModifierObject* CreateObject();
};




class MKModifier {
public:
	void ActivateModifier(BaseModifier* modifier, MKCharacter* obj);
};



