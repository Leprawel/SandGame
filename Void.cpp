#include "Void.hpp"

Void::Void() : CellBase(0, "Void", sf::Color(0, 0, 0, 0)) {}

void Void::ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) { return; }

void Void::Reset() {};