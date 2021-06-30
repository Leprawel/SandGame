#include "Border.hpp"

Border::Border() : CellBase(-1, "Border", sf::Color(0, 0, 0, 0)) {}

void Border::ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) { return; }

void Border::Reset() {};