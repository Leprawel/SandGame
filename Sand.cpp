#include "Sand.hpp"

Sand::Sand() : CellType(1, "Sand", sf::Color(255, 255, 255, 255)) {}

void Sand::CalculateRule(unsigned int* result, unsigned int x, unsigned int y, const SandWorld& world){
	result[0] = x;
	result[1] = y;
	if (world.GetWithBorders(x, y + 1) == 0) {
		result[0] = x;
		result[1] = y + 1;
	}
	else if (world.GetWithBorders(x - 1, y + 1) == 0) {
		result[0] = x - 1;
		result[1] = y + 1;
	}
	else if (world.GetWithBorders(x + 1, y + 1) == 0) {
		result[0] = x + 1;
		result[1] = y + 1;
	}
}