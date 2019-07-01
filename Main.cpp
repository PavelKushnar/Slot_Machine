
#include <SFML/Graphics.hpp>
#include <vector> 
#include <iostream> 
#include "slots.h" 

using namespace sf;

class Line { 
public:
	float x, y, w=172, h=172, speed = 1.5; 
	int line,num;
	Image image;
	Texture texture;
	Sprite lineSprites[25];
	Clock clTimer;
	float distance = 0;
	float distanceStop = 0;
	bool stop = false, isgame = false;
	
	
	Line(int Line, float X, int Num) {  

		line = Line;
		image.loadFromFile("images/numbers.png");
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		x = X; //отступ от левого края
		num = Num;

		for (int i = 0; i < HEIGHT_slots ; i++) 
		{
			
			lineSprites[i].setTexture(texture);
			if (TileSlots[i][line] == 97) lineSprites[i].setTextureRect(IntRect(21, 0, 172, 172));
			if (TileSlots[i][line] == 98) lineSprites[i].setTextureRect(IntRect(153, 0, 172, 172));
			if (TileSlots[i][line] == 99) lineSprites[i].setTextureRect(IntRect(337, 0, 172, 172));
			if (TileSlots[i][line] == 100) lineSprites[i].setTextureRect(IntRect(563, 0, 172, 172));
			if (TileSlots[i][line] == 101) lineSprites[i].setTextureRect(IntRect(783, 0, 172, 172));
			if (TileSlots[i][line] == 102) lineSprites[i].setTextureRect(IntRect(1005, 0, 172, 172));
			lineSprites[i].setPosition(x, 452 - i * 172);
		}
	}

	void restart() {
		for (int i = 0; i < HEIGHT_slots; i++) {
			for (int j = 0; j < WIDTH_slots; j++) {
				TileSlots[i][line] = getRandomNumber(97, 102);
			}
		}
		image.loadFromFile("images/numbers.png");
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);

		for (int i = 0; i < HEIGHT_slots; i++) 
		{

			lineSprites[i].setTexture(texture);
			if (TileSlots[i][line] == 97) lineSprites[i].setTextureRect(IntRect(21, 0, 172, 172));
			if (TileSlots[i][line] == 98) lineSprites[i].setTextureRect(IntRect(153, 0, 172, 172));
			if (TileSlots[i][line] == 99) lineSprites[i].setTextureRect(IntRect(337, 0, 172, 172));
			if (TileSlots[i][line] == 100) lineSprites[i].setTextureRect(IntRect(563, 0, 172, 172));
			if (TileSlots[i][line] == 101) lineSprites[i].setTextureRect(IntRect(783, 0, 172, 172));
			if (TileSlots[i][line] == 102) lineSprites[i].setTextureRect(IntRect(1005, 0, 172, 172));
			lineSprites[i].setPosition(x, 452 - i * 172);
		}
		distance = 0;
		distanceStop = 0;
		isgame = true;

	}

	int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

	void fastStop()
	{	
		if(isgame == true){
			
			for (int i = 0; i < HEIGHT_slots; i++) 
			{
				float y = lineSprites[i].getPosition().y;

				lineSprites[i].setPosition(lineSprites[i].getPosition().x, 452 - i * 172 + num*172);
			}
			distance = num * 172;
		}
	}
	void update(float time) 
	{
		distance += speed * time;
		if(distance<num*172+240)
			if (distance < num * 172)
				for (int i = 0; i < HEIGHT_slots; i++) 
				{
					float y = lineSprites[i].getPosition().y;

					lineSprites[i].setPosition(lineSprites[i].getPosition().x, y += speed * time);
				}
			else {

				distanceStop += speed * time;
				float coefSpeed;
				if(distanceStop<120)coefSpeed = 0.5; else coefSpeed = -0.5;
					for (int i = 0; i < HEIGHT_slots; i++) 
					{
						float y = lineSprites[i].getPosition().y;

						lineSprites[i].setPosition(lineSprites[i].getPosition().x, y += coefSpeed*speed * time);
					}
					if (distanceStop < 120)isgame = false;
				}
	}
};


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
	Line p(0, 186,8);
	Line p1(1, 388,11);
	Line p2(2, 590,14);
	Line p3(3, 792,17);
	Line p4(4, 994,20);
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
				if (event.key.code == sf::Keyboard::E) 
				{
					p.restart();
					p1.restart();
					p2.restart();
					p3.restart();
					p4.restart();
				}
				if (event.key.code == sf::Keyboard::Space) 
				{
					p.fastStop();
					p1.fastStop();
					p2.fastStop();
					p3.fastStop();
					p4.fastStop();
				}
			}
		}
			p.update(time);
			p1.update(time);
			p2.update(time);
			p3.update(time);
			p4.update(time);
		window.clear();
		for (int i = 0; i < HEIGHT_slots; i++) {
			window.draw(p.lineSprites[i]);
			window.draw(p1.lineSprites[i]);
			window.draw(p2.lineSprites[i]);
			window.draw(p3.lineSprites[i]);
			window.draw(p4.lineSprites[i]);
		}
		window.draw(backgroundsprite);
		
		window.display();
	}

	return 0;
}