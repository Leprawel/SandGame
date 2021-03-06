#pragma once
#include "CellBase.hpp"

class Sand : public CellBase {
public:
	Sand();

	void ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) override;

	void Reset() override;
};