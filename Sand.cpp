#include "Sand.hpp"

Sand::Sand() : CellBase(1, "Sand", sf::Color(255, 255, 255, 255)) {}

void Sand::ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world){
	int result[2] = { x, y };
	CellBase* check = world.At(x, y + 1);
	if (check->id == 0 || check->id == 2) {
		result[0] = x;
		result[1] = y + 1;
	}
	else {
		check = world.At(x - 1, y + 1);
		if (check->id == 0 || check->id == 2) {
			result[0] = x - 1;
			result[1] = y + 1;
		}
		else {
			check = world.At(x + 1, y + 1);
			if (check->id == 0 || check->id == 2) {
				result[0] = x + 1;
				result[1] = y + 1;
			}
		}
	}
	world.Move(x, y, result[0], result[1]);
	world.MarkComputed(result[0], result[1]);
}

void Sand::Reset() {};