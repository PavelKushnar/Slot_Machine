#include <SFML/Graphics.hpp>
#include <vector> 
#include <iostream> 
#include "slots.h" 
#include "Line.h" 
using namespace sf;

int Line::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Line::startPosition(){
	for (int i = 0; i < HEIGHT_slots; i++){
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
	
Line::Line(int Line, float X, int Num) {

		line = Line;
		image.loadFromFile("images/numbers.png");
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		x = X; //отступ от левого края
		num = Num;
		startPosition();
}

void Line::restart(){
	
		for (int i = 0; i < HEIGHT_slots; i++) {
			for (int j = 0; j < WIDTH_slots; j++) {
				TileSlots[i][line] = getRandomNumber(97, 102);
			}
		}
		image.loadFromFile("images/numbers.png");
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		startPosition();
		distance = 0;
		distanceStop = 0;
		isgame = true;
	
}

void Line::fastStop(){	
	if (isgame == true && distance < num * 172) {

		for (int i = 0; i < HEIGHT_slots; i++)
		{
			float y = lineSprites[i].getPosition().y;

			lineSprites[i].setPosition(lineSprites[i].getPosition().x, 452 - i * 172 + num * 172);
		}
		distance = num * 172;
	}
}

void Line::update(float time){
	distance += speed * time;
	if (isgame)
		if (distance < num * 172)
			for (int i = 0; i < HEIGHT_slots; i++)
			{
				float y = lineSprites[i].getPosition().y;

				lineSprites[i].setPosition(lineSprites[i].getPosition().x, y += speed * time);
			}
			else {
				distanceStop += speed * time;
				if (distanceStop < 240)coefSpeed = 0.5; else coefSpeed = -0.5;
				for (int i = 0; i < HEIGHT_slots; i++)
				{
					float y = lineSprites[i].getPosition().y;

					lineSprites[i].setPosition(lineSprites[i].getPosition().x, y += coefSpeed * speed * time);
				}
				if (distanceStop > 480)
				{
					isgame = false;
					for (int i = 0; i < HEIGHT_slots; i++)
					{
						lineSprites[i].setPosition(lineSprites[i].getPosition().x, 452 - i * 172 + num * 172);
					}
				}
			}
}

Sprite Line::getLineSprite(int i)
{
	return lineSprites[i];
}

bool Line::getState()
{
	return isgame;
}
