#pragma once
#include "CellBase.hpp"

class Void : public CellBase {
public:
	Void();

	void ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) override;

	void Reset() override;
};