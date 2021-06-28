#include "CellType.hpp"


CellType::CellType(unsigned char i, std::string n, sf::Color c) : id(i), name(n) {
	color = c;
}