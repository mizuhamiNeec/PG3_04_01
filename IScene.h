#pragma once
#include <vector>

enum SCENE_ID {
	SCENE_ID_NONE = 0,
	SCENE_ID_TITLE,
	SCENE_ID_GAME,
	SCENE_ID_CLEAR,
	SCENE_ID_MAX
};

class IScene {
public:
	virtual void Init() = 0;
	virtual void Update(std::vector<char>& keys, std::vector<char>& preKeys) = 0;
	virtual void Draw() = 0;

	virtual ~IScene() = default;

	static int GetSceneNo();

protected:
	static int sceneNo_;
};

