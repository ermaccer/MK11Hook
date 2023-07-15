#pragma once
#include "..\utils.h"
#include "MKObject.h"

class Krypt {
public:
	static Krypt* pKrypt;
	static void FindKrypt();

	MKObject* GetKryptPlayer(int value);
};

Krypt* GetKrypt();