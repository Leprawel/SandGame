#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "SandWorld.hpp"
#include "CellType.hpp"
#include "Sand.hpp"

void DrawSandWorld(const SandWorld& world, sf::RenderWindow& window) {
	unsigned int width = world.GetWidth();
	unsigned int height = world.GetHeight();
	sf::Texture texture;
	texture.create(width, height);
	sf::Uint8 * color = new sf::Uint8[width * height * 4];

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			sf::Color cl = world.GetType(x, y)->color;
			color[(y * width + x) * 4] = cl.r;
			color[(y * width + x) * 4 + 1] = cl.g;
			color[(y * width + x) * 4 + 2] = cl.b;
			color[(y * width + x) * 4 + 3] = cl.a;

		}
	}
	
	texture.update(color);
	delete[] color;
	window.draw(sf::Sprite(texture));
}

void RunSimulation(SandWorld& world, sf::RenderWindow& window, float maxFps = 0) {
	//std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		DrawSandWorld(world, window);
		//std::cout << "Draw time: " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << "\n";

		auto start = std::chrono::high_resolution_clock::now();
		world.Update();
		std::cout << "Update FPS: " << 1/std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << "\n";

		world.Set(300, 0, 1);
		world.Set(400, 0, 1);
		world.Set(500, 0, 1);
		world.Set(600, 0, 1);
		world.Set(700, 0, 1);
		world.Set(551, 700, 2);
		world.Set(552, 700, 2);
		world.Set(553, 700, 2);
		world.Set(554, 700, 2);
		world.Set(555, 700, 2);
		world.Set(556, 700, 2);

		window.display();

		/*std::chrono::high_resolution_clock::time_point newFrame = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newFrame - lastFrame);
		if (maxFps > 0 && deltaTime.count() < 1/maxFps) {
			std::this_thread::sleep_for(std::chrono::duration<float>(1 / maxFps) - deltaTime);
		}*/
		//std::cout << "\nFps: " << 1 / std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastFrame).count();
		//lastFrame = newFrame;
	}
}

//void sandFunc(unsigned int * result, unsigned int x, unsigned int y, const SandWorld& world) {
//	result[0] = x;
//	result[1] = y;
//	if (world.GetWithBorders(x, y + 1) == 0) {
//		result[0] = x;
//		result[1] = y + 1;
//	}
//	else if (world.GetWithBorders(x - 1, y + 1) == 0) {
//		result[0] = x - 1;
//		result[1] = y + 1;
//	}
//	else if (world.GetWithBorders(x + 1, y + 1) == 0) {
//		result[0] = x + 1;
//		result[1] = y + 1;
//	}
//}

//void waterFunc(unsigned int* result, unsigned int x, unsigned int y, const SandWorld& world) {
//	result[0] = x;
//	result[1] = y;
//	bool bul = rand() % 2;
//	if (world.GetWithBorders(x, y + 1) == 0) {
//		result[0] = x;
//		result[1] = y + 1;
//	}
//	else
//	{
//		bool left = world.GetWithBorders(x - 1, y + 1) == 0;
//		bool right = world.GetWithBorders(x + 1, y + 1) == 0;
//		if (left && !right || (bul && left && right)) {
//			result[0] = x - 1;
//			result[1] = y + 1;
//		}
//		else if (right && !left || (!bul && left && right)) {
//			result[0] = x + 1;
//			result[1] = y + 1;
//		}
//		else {
//			bool left = world.GetWithBorders(x - 1, y) == 0;
//			bool right = world.GetWithBorders(x + 1, y) == 0;
//			if (left && !right || (bul && left && right)) {
//				result[0] = x - 1;
//				result[1] = y;
//			}
//			else if (right && !left || (!bul && left && right)) {
//				result[0] = x + 1;
//				result[1] = y;
//			}
//		}
//	}
//}

int main()
{
	srand(time(0));
	unsigned int width = 1600;
	unsigned int height = 900;
	SandWorld world(width, height, 0);
	world.SetCellType(new Sand());

	sf::RenderWindow window(sf::VideoMode(width, height), "Conways Game of Life!");

	RunSimulation(world, window);

	return 0;
}