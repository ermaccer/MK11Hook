#pragma once
#include "../mk/MKCharacter.h"
#include "../mk/PlayerInfo.h"
#include "../unreal/TArray.h"
#include "../utils.h"

class BaseModifier {
public:
	char data[112] = {};
};

class Modifier : public BaseModifier {
public:
	Modifier(const char* name);

	void GetAssetPath(TArray<char>& path);
};

class ModifierObject {
public:
	char data[512] = {};

	ModifierObject(Modifier* modifier, int flags);

	void Activate(MKCharacter* p1, MKCharacter* p2);
};




class TagAssistModifier : public BaseModifier {
public:
	TagAssistModifier(const char* character);
	void Activate(PlayerInfo* info);
};

class MKModifier {
public:
	static Modifier* CreateModifier(const char* name);
	static void		 ActivateModifier(Modifier* mod, int playerFlags);
};


MKModifier* GetModifierManager();
void		LoadModifierAssets();