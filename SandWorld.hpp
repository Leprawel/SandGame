#pragma once
#include "CellType.hpp"

class CellType;

class SandWorld {
	unsigned char* cells;
	bool* computed;
	unsigned int width;
	unsigned int height;
	//Array of pointers because i want to have nullptr for undefined cell types
	CellType** definedCells;

public:
	SandWorld() = delete;

	SandWorld(unsigned int w, unsigned int h, unsigned char fill);

	//It is doubtful this is working correctly
	//SandWorld(const SandWorld& other);

	~SandWorld();

	unsigned int Get(unsigned int x, unsigned int y) const;
	CellType * GetType(unsigned int x, unsigned int y) const;
	int GetWithBorders(long long x, long long y) const;
	void Set(unsigned int x, unsigned int y, unsigned char newVal);
	unsigned int GetHeight() const;
	unsigned int GetWidth() const;

	void Update();

	void SetCellType(CellType* type);

	void PrintToConsole();
};