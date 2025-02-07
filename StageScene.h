#pragma once
#include <list>
#include <memory>

#include <base/WinApp.h>

#include "IScene.h"
#include "StageSceneInputHandler.h"
#include "Vec2.h"

class StageScene final : public IScene {
public:
	void Init() override;
	void Update(std::vector<char>& keys, std::vector<char>& preKeys) override;
	void Draw() override;

private:
	std::unique_ptr<StageSceneInputHandler> inputHandler_ = nullptr;
	std::unique_ptr<IStageSceneCommand> command_ = nullptr;
	std::list<IStageSceneCommand*> commandHistory_;
	std::list<IStageSceneCommand*>::iterator commandHistoryItr_;

	Selector* selector_;
};

