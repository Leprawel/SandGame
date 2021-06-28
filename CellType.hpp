#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SandWorld.hpp"

class SandWorld;

class CellType {
public:
	const unsigned char id;
	const std::string name;
	sf::Color color;

	CellType(unsigned char i, std::string n, sf::Color c);

	virtual void CalculateRule(unsigned int * result, unsigned int x, unsigned int y, const SandWorld& world) = 0;
};