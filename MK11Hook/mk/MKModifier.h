#pragma once
#include "../mk/MKCharacter.h"
#include "../mk/PlayerInfo.h"
#include "../utils.h"

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


MKModifier* GetModifierManager();
void		LoadModifierAssets();