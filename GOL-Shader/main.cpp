#include <SFML/Graphics.hpp>

#include <random>

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GOL");

	sf::Image image;
	image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color());

	for (int i = 0; i < WINDOW_WIDTH; i++) 
		for (int j = 0; j < WINDOW_HEIGHT; j++) {
			if (rand() % 2 == 0) {
				image.setPixel(i, j, sf::Color::White);
			}
		}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(sprite);
		
		window.display();
	}

	return 0;
}