#pragma once
#include "CellType.hpp"

class Sand : public CellType {
public:
	Sand();

	void CalculateRule(unsigned int* result, unsigned int x, unsigned int y, const SandWorld& world) override;
};