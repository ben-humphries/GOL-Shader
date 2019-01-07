#include <SFML/Graphics.hpp>

#include <random>

const int WINDOW_SIZE = 400;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "GOL");

	sf::Image image;
	image.create(WINDOW_SIZE, WINDOW_SIZE, sf::Color());

	for (int i = 0; i < WINDOW_SIZE; i++) 
		for (int j = 0; j < WINDOW_SIZE; j++) {
			if (rand() % 2 == 0) {
				image.setPixel(i, j, sf::Color::White);
			}
		}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::Shader fragmentShader;

	if (!fragmentShader.loadFromFile("fragment.glsl", sf::Shader::Fragment)) {
		printf("Could not load shader.");
	}

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 0) {
			clock.restart();

			window.clear();

			fragmentShader.setUniform("aTexture", sf::Shader::CurrentTexture);
			fragmentShader.setUniform("windowSize", (float) WINDOW_SIZE);
			window.draw(sprite, &fragmentShader);
			texture.update(window);

			window.display();

		}
	}

	return 0;
}