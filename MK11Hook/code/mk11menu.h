#pragma once
// as usual, based on mh2 debug menu

class MK11Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool	 bSlowMotionEnabled;
	float	 fSlowMotionSpeed;

	void Initialize();
	void Process();
	void UpdateControls();
};


extern MK11Menu* TheMenu;