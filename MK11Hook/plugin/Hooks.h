#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKModifier.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

extern void(__fastcall* pProcessDOFSettings)(int64, int64, int64, int64);
void ProcessDOFSettings(int64 settings, int64 a2, int64 newSettings, int64 a4);

void MKProcDispatch_Hook();
void Dispatch_Hook(int64 ptr, int a2);
void RecordEvent_Hook(int64 eventID, int64 a2, int64 a3, int64 a4);

void SetSelectScreen_Hook(int64 ptr, PLAYER_NUM plr, int teamNo, char* name, int level, int64 loadout, bool altPalette);
void SetCharacterLadder_Hook(CharacterDefinition* chr, char* name, int64 ptr, int64 unk);

void   ReadPropertyValue_Hook(int64 ptr, int* unk, int* value);
int64  SetProperty(int64 ptr, char* name, int64 unk);


void SetKryptCharacter(int64 ptr, char* name);
void SetKryptCharacterL(int64 ptr, char* name, int unk);
void SetKryptCharacterClass(int64 ptr, char* name, int unk);


void PluginDispatch();
void PluginFightStartup();