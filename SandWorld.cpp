#include "SandWorld.hpp"
#include "Void.hpp"
#include <iostream>

SandWorld::SandWorld(unsigned int w, unsigned int h, unsigned char fill = 0) {
	width = w;
	height = h;
	cells = new unsigned char[w * h];
	memset(cells, fill, width * height * sizeof(unsigned char));
	computed = new bool[w * h];
	memset(computed, 0, width * height * sizeof(bool));
	definedCells = new CellType * [256];
	std::fill(definedCells, definedCells + 256, nullptr);
	definedCells[0] = new Void();
}

//SandWorld::SandWorld(const SandWorld& other) {
//	width = other.width;
//	height = other.height;
//	memcpy(cells, other.cells, width * height * sizeof(unsigned char));
//	memcpy(computed, other.computed, width * height * sizeof(bool));
//	for (unsigned int i = 0; i < 256; i++) {
//		definedCells[i] = other.definedCells[i];
//	}
//}

SandWorld::~SandWorld() {
	delete[] cells;
	delete[] computed;
	delete[] definedCells;
}

unsigned int SandWorld::Get(unsigned int x, unsigned int y) const {
	if (x >= width || y >= height) throw std::out_of_range("Position outside the cells array.");
	return cells[y * width + x];
}

CellType * SandWorld::GetType(unsigned int x, unsigned int y) const {
	unsigned char type = Get(x, y);
	CellType* result = definedCells[type];
	if (result) return result;
	else return definedCells[0];
}

int SandWorld::GetWithBorders(long long x, long long y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) return -1;
	else return cells[y * width + x];
}

void SandWorld::Set(unsigned int x, unsigned int y, unsigned char newVal) {
	if (x >= width || y >= height) throw std::out_of_range("Position outside the cells array");
	cells[y * width + x] = newVal;
}
unsigned int SandWorld::GetHeight() const { return height; }
unsigned int SandWorld::GetWidth() const { return width; }

void SandWorld::Update() {
	memset(computed, 0, width * height * sizeof(bool));

	for (unsigned int y = height-1; y < height; y--) {
		for (unsigned int x = 0; x < width; x+=2) {
			if (!computed[y * width + x]) {
				unsigned char cellVal = cells[y * width + x];
				unsigned int newPos[2];
				CellType* cell = definedCells[cellVal];
				if (cell) {
					cell->CalculateRule(newPos, x, y, *this);
					if (newPos[0] != x || newPos[1] != y) {
						Set(x, y, 0);
						Set(newPos[0], newPos[1], cellVal);
					}
					computed[newPos[1] * width + newPos[0]] = true;
				}
			}
		}
		for (unsigned int x = 1; x < width; x += 2) {
			if (!computed[y * width + x]) {
				unsigned char cellVal = cells[y * width + x];
				unsigned int newPos[2];
				CellType* cell = definedCells[cellVal];
				if (cell) {
					cell->CalculateRule(newPos, x, y, *this);
					if (newPos[0] != x || newPos[1] != y) {
						Set(x, y, 0);
						Set(newPos[0], newPos[1], cellVal);
					}
					computed[newPos[1] * width + newPos[0]] = true;
				}
			}
		}
	}

}

void SandWorld::SetCellType(CellType* type) {
	if (type->id == 0) throw std::invalid_argument("Cell id cannot be 0.");
	else definedCells[type->id] = type;
}

void SandWorld::PrintToConsole() {
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			std::cout << int(Get(x, y)) << "\t";
		}
		std::cout << "\n";
	}
}