#include <SFML/Graphics.hpp>
#include <vector> 
#include <iostream> 
#include "Line.h" 

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1366, 768), "Lost machine");

	Image image;
	Image numbersimage;

	numbersimage.loadFromFile("Images/numbers.png");
	numbersimage.createMaskFromColor(Color(0, 0, 0));

	Texture numbertexture;
	numbertexture.loadFromImage(numbersimage);

	Texture background;
	background.loadFromFile("Images/background.png");

	Sprite backgroundsprite;
	backgroundsprite.setTexture(background);

	Clock clock;
	std::vector<Line> lines;
	lines.push_back(Line(0, 186, 8));
	lines.push_back(Line(1, 388, 11));
	lines.push_back(Line(2, 590, 14));
	lines.push_back(Line(3, 792, 17));
	lines.push_back(Line(4, 994, 20));
	for (int i = 0; i < lines.size(); i++) {
		lines[i].restart();
	}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		
		time = time/1000 ;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) 
			{
				if (event.key.code == sf::Keyboard::E && !lines.back().getState())
				{
					for (int i = 0; i < lines.size(); i++) {
						lines[i].restart();
					}
				}
				if (event.key.code == sf::Keyboard::Space) 
				{
					for (int i = 0; i < lines.size(); i++) {
						lines[i].fastStop();
					}
				}
			}
		}
		for (int i = 0; i < lines.size(); i++) {
			lines[i].update(time);
		}
		window.clear();
		for (int i = 0; i < 25; i++) {
			for (int l = 0; l < lines.size(); l++) {
				window.draw(lines[l].getLineSprite(i));
			}
		}
		window.draw(backgroundsprite);
		window.display();
	}

	return 0;
}