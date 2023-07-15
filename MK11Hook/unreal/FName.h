#pragma once
#include "TArray.h"
#include "..\utils.h"

enum EFindName
{
	FNAME_Find,
	FNAME_Add,
	FNAME_Replace,
};

struct FNameEntry {
	char pad[16];
	char name[128];
};

class FName {
public:
	int Index;
	int Number;

	FName();
	FName(const char* Name, EFindName FindType, int formal);
};


TArray<FNameEntry*>* GetNames();

char* GetName(int index);