#pragma once
#include "CellBase.hpp"

class CellBase;

class SandWorld {
	// Simulation world
	CellBase** space;
	bool* computed;
	unsigned int width;
	unsigned int height;
	size_t spaceSize;

	CellBase* emptyCell;
	CellBase* borderCell;
	const size_t NUMBER_OF_CELL_TYPES = 3;

public:

	SandWorld() = delete;

	SandWorld(unsigned int w, unsigned int h, unsigned char fill);

	SandWorld(const SandWorld& other) = delete;

	~SandWorld();

	//Fast at, no safety measures
	CellBase* Fat(unsigned int x, unsigned int y);
	//Safe at, returns Void for empty cells and Border for cells outside space
	CellBase* At(unsigned int x, unsigned int y);

	sf::Color ColorAt(unsigned int x, unsigned int y) const;

	void Set(unsigned int x, unsigned int y, CellBase* cell);

	void SetAtRatio(double x, double y, CellBase* cell);

	void Move(unsigned int originX, unsigned int originY, unsigned int targetX, unsigned int targetY);

	void MarkComputed(unsigned int x, unsigned int y);
	bool IsComputed(unsigned int x, unsigned int y);
	unsigned int GetHeight() const;
	unsigned int GetWidth() const;

	void Update();

	void ComputeCell(unsigned int x, unsigned int y);

	CellBase* GetCellFromVault(size_t cellId);

};