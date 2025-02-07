#pragma once
#include "IStageSceneCommand.h"
#include "Unit.h"

class StageSceneInputHandler {
public:
	StageSceneInputHandler();
	void UpdateKeyState();

	IStageSceneCommand* SelectorHandleInput(Selector* selector);
	IStageSceneCommand* UnitHandleInput(Unit* unit);

	bool CheckUndoStatus();
private:
	char keys_[256] = { 0 };
	char preKeys_[256] = { 0 };
	Selector* selector_;
	Unit* selectedUnit_;
};
