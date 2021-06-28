#pragma once
#include "CellType.hpp"

class Void : public CellType {
public:
	Void();

	void CalculateRule(unsigned int* result, unsigned int x, unsigned int y, const SandWorld& world) override;
};