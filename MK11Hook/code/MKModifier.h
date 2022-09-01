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


class Modifier : public BaseModifier {
public:
	Modifier(const char* character, int a3, int a4, char* a5);
	void Activate(MKCharacter* who);
};

class ModifierAssistObject {
public:
	void Activate(MKCharacter* obj);
};


class ModifierAssist : public BaseModifier {
public:
	ModifierAssist(const char* name, int a3, int a4, char* a5);
	ModifierAssistObject* CreateObject();
};

class MKModifier {
public:
	void ActivateModifier(BaseModifier* modifier, MKCharacter* obj);
};



