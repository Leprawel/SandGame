#pragma once
#include "CellBase.hpp"

class Border : public CellBase {
public:
	Border();

	void ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) override;

	void Reset() override;
};