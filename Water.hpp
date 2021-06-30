#pragma once
#include "CellBase.hpp"

class Water : public CellBase {
public:

	Water();

	void ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) override;

	void Reset() override;
};