#pragma once

class Unit;

class Selector {
public:
	Selector();

	void Init();
	void Update();
	void Draw();

	void Move(int x, int y);
	void SelectUnit();

	int GetMapSize() const { return mapSize_; }
	int GetSelectMode() const { return selectMode_; }
	Unit* GetSelectedUnit() const { return selectedUnit_; }
	int GetMapX() const { return mapX_; }
	int GetMapY() const { return mapY_; }

private:
	int mapX_;
	int mapY_;
	int mapSize_;

	int selectMode_;

	Unit* unit_;
	Unit* selectedUnit_;
};
