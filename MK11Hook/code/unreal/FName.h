#pragma once

enum EFindName
{
	FNAME_Find,
	FNAME_Add,
	FNAME_Replace,
};


class FName {
private:
	int Index;
	int Number;
public:
	FName(const char* Name, EFindName FindType, int formal);
};