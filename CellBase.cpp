#include "CellBase.hpp"


CellBase::CellBase(unsigned char i, std::string n, sf::Color c) : id(i), name(n) {
	dirSwitch = true;
	color = c;
}