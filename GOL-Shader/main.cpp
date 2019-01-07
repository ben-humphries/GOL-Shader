#include <SFML/Graphics.hpp>

#include <random>

const int WINDOW_SIZE = 1000;

const int GAME_SIZE = 500;

const float MAX_FPS = 120;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "GOL");

	sf::RenderTexture rtexture;
	if (!rtexture.create(GAME_SIZE, GAME_SIZE)) {
		printf("Could not create render texture.");
	}


	sf::Image image;
	image.create(GAME_SIZE, GAME_SIZE, sf::Color());

	for (int i = 0; i < GAME_SIZE; i++) 
		for (int j = 0; j < GAME_SIZE; j++) {
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

		if (clock.getElapsedTime().asSeconds() > 1 / MAX_FPS) {
			clock.restart();

			rtexture.clear();

			fragmentShader.setUniform("aTexture", sf::Shader::CurrentTexture);
			fragmentShader.setUniform("windowSize", (float) GAME_SIZE);
			rtexture.draw(sprite, &fragmentShader);
			texture.update(rtexture.getTexture());

			rtexture.display();

			window.clear();
			sf::Sprite fsprite(rtexture.getTexture());
			float scale = (float)WINDOW_SIZE / (float)GAME_SIZE;
			fsprite.setScale(scale, scale);
			window.draw(fsprite);
			window.display();

		}
	}

	return 0;
}