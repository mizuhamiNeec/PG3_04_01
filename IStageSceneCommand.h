#pragma once

class IStageSceneCommand {
public:
	virtual ~IStageSceneCommand() = default;
	virtual void Exec() = 0;
};
