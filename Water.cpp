#include "Water.hpp"

Water::Water() : CellBase(2, "Water", sf::Color(100, 100, 255, 255)) {}

void Water::ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) {
	int result[2] = { x, y };
	if (world.At(x, y + 1)->id == 0) {
		result[0] = x;
		result[1] = y + 1;
	}
	else
	{
		bool left = world.At(x - 1, y + 1)->id == 0;
		bool right = world.At(x + 1, y + 1)->id == 0;
		if (left && !right || (dirSwitch && left && right)) {
			dirSwitch = !dirSwitch;
			result[0] = x - 1;
			result[1] = y + 1;
		}
		if (right && !left || (!dirSwitch && left && right)) {
			dirSwitch = !dirSwitch;
			result[0] = x + 1;
			result[1] = y + 1;
		}
		else {
			left = world.At(x - 1, y)->id == 0;
			right = world.At(x + 1, y)->id == 0;
			if (left && !right || (dirSwitch && left && right)) {
				dirSwitch = !dirSwitch;
				result[0] = x - 1;
				result[1] = y;
			}
			else if (right && !left || (!dirSwitch && left && right)) {
				dirSwitch = !dirSwitch;
				result[0] = x + 1;
				result[1] = y;
			}
		}
	}
	world.Move(x, y, result[0], result[1]);
	world.MarkComputed(result[0], result[1]);
}

void Water::Reset() {};