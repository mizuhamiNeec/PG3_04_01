#pragma once
#include "IScene.h"

class TitleScene final : public IScene {
public:
	void Init() override;
	void Update(std::vector<char>& keys, std::vector<char>& preKeys) override;
	void Draw() override;
};

