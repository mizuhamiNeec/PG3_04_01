#pragma once
#include <mutex>
#include <thread>

#include <base/WinApp.h>

#include "IScene.h"
#include "Vec2.h"

class GameScene final : public IScene
{
public:
	void Init() override;
	void Update(std::vector<char> &keys, std::vector<char> &preKeys) override;
	void Draw() override;

	~GameScene() override;

private:
	void LoadCSV();
	std::vector<std::vector<int>> mapData_;
	bool csvLoaded_ = false;
	std::thread loadThread_;
	std::mutex mapDataMutex_;
};
