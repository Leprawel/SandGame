#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SandWorld.hpp"

class SandWorld;

class CellBase {
public:
	bool dirSwitch;
	const int id;
	const std::string name;
	sf::Color color;

	CellBase(unsigned char i, std::string n, sf::Color c);

	virtual void ExecuteBehaviour(unsigned int x, unsigned int y, SandWorld& world) = 0;

	virtual void Reset() = 0;
};