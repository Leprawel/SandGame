#include <iostream>
#include "SandWorld.hpp"
#include "CellBase.hpp";
#include "Void.hpp";
#include "Sand.hpp"
#include "Water.hpp"
#include "Border.hpp"

SandWorld::SandWorld(unsigned int w, unsigned int h, unsigned char fill = 0) {
	width = w;
	height = h;
	spaceSize = width * height;

	emptyCell = new Void();
	borderCell = new Border();

	space = new CellBase* [spaceSize];
	std::fill(space, space + spaceSize, nullptr);

	computed = new bool[spaceSize];
	memset(computed, 0, spaceSize * sizeof(bool));
}

SandWorld::~SandWorld() {
	delete[] space;
	delete[] computed;
}

CellBase* SandWorld::Fat(unsigned int x, unsigned int y) {
	//if (x >= width || y >= height) throw std::out_of_range("Position outside the space array.");
	return space[y * width + x];
}

CellBase* SandWorld::At(unsigned int x, unsigned int y) {
	if (x < 0 || x >= width || y < 0 || y >= height) return borderCell;
	else if (Fat(x, y)) return Fat(x, y);
	else return emptyCell;
}

sf::Color SandWorld::ColorAt(unsigned int x, unsigned int y) const {
	CellBase* result = space[y * width + x];
	if (result) return result->color;
	else return sf::Color(0, 0, 0, 0);
}

void SandWorld::Set(unsigned int x, unsigned int y, CellBase* cell) {
	//if (x >= width || y >= height) throw std::out_of_range("Position outside the space array");
	if (space[y * width + x]) {
		delete cell;
		return;
	}
	else {
		space[y * width + x] = cell;
	}
}

void SandWorld::SetAtRatio(double x, double y, CellBase* cell) {
	//if (x < 0 || x > 1 || y < 0 || y > 1) throw std::out_of_range("Position outside the space array");
	unsigned int posX = int(x * width);
	unsigned int posY = int(y * height);
	Set(posX, posY, cell);
}

void SandWorld::Move(unsigned int originX, unsigned int originY, unsigned int targetX, unsigned int targetY) {
	if (At(targetX, targetY)->id == 0) {
		space[targetY * width + targetX] = Fat(originX, originY);
		space[originY * width + originX] = nullptr;
	}
	else {
		CellBase* moveTarget = Fat(targetX, targetY);
		space[targetY * width + targetX] = Fat(originX, originY);
		space[originY * width + originX] = moveTarget;
	}
}

void SandWorld::MarkComputed(unsigned int x, unsigned int y) {
	computed[y * width + x] = true;
}
bool SandWorld::IsComputed(unsigned int x, unsigned int y) {
	return computed[y * width + x];
}
unsigned int SandWorld::GetHeight() const { return height; }
unsigned int SandWorld::GetWidth() const { return width; }

void SandWorld::Update() {
	memset(computed, 0, spaceSize * sizeof(bool));

	for (unsigned int y = height-1; y < height; y--) {
		for (unsigned int x = 0; x < width; x+=2) {
			ComputeCell(x, y);
		}
		for (unsigned int x = 1; x < width; x += 2) {
			ComputeCell(x, y);
		}
	}
}

void SandWorld::ComputeCell(unsigned int x, unsigned int y) {
	if (!computed[y * width + x]) {
		CellBase* cell = space[y * width + x];
		if (cell) {
			cell->ExecuteBehaviour(x, y, *this);
		}
	}
}