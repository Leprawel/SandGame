#include "Void.hpp"

Void::Void() : CellType(0, "Void", sf::Color(0, 0, 0, 0)) {}

void Void::CalculateRule(unsigned int* result, unsigned int x, unsigned int y, const SandWorld& world) { result[0] = x; result[1] = y; }