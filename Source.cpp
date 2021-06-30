#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "SandWorld.hpp"
#include "CellBase.hpp"
#include "Sand.hpp"
#include "Water.hpp"

void DrawSandWorld(const SandWorld& world, sf::RenderWindow& window) {
	unsigned int width = world.GetWidth();
	unsigned int height = world.GetHeight();
	sf::Texture texture;
	texture.create(width, height);
	sf::Uint8 * color = new sf::Uint8[width * height * 4];

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			sf::Color cl = world.ColorAt(x, y);
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
	std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();

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

		world.SetAtRatio(0.4, 0.1, new Sand());
		world.SetAtRatio(0.55, 0.1, new Sand());
		world.SetAtRatio(0.6, 0.1, new Sand());
		world.SetAtRatio(0.49, 0.6, new Water());
		world.SetAtRatio(0.5, 0.6, new Water());
		world.SetAtRatio(0.51, 0.6, new Water());

		window.display();

		std::chrono::high_resolution_clock::time_point newFrame = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newFrame - lastFrame);
		if (maxFps > 0 && deltaTime.count() < 1/maxFps) {
			std::this_thread::sleep_for(std::chrono::duration<float>(1 / maxFps) - deltaTime);
		}
		//std::cout << "\nFps: " << 1 / std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastFrame).count();
		lastFrame = newFrame;
	}
}

int main()
{
	srand(time(0));
	unsigned int width = 500;
	unsigned int height = 500;
	SandWorld world(width, height, 0);

	sf::RenderWindow window(sf::VideoMode(width, height), "Sand World!");

	RunSimulation(world, window);

	return 0;
}