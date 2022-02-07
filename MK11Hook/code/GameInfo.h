#pragma once

class FGGameInfo {
public:
	void SetStage(const char* stage);
	void ResetStageInteractables();
};

FGGameInfo* GetGameInfo();