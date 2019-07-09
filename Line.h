#include <vector> 
using namespace sf;

class Line {
private:
	float x, y, w = 172, h = 172, speed = 1.5;
	int line, num;
	Image image;
	Texture texture;
	Sprite lineSprites[25];
	Clock clTimer;
	float distance = 0;
	float distanceStop = 0;
	float coefSpeed;
	bool stop = false, isgame = false;
	int getRandomNumber(int min, int max);
	void startPosition();
public:
	Line(int Line, float X, int Num);
	void restart();
	void fastStop();
	void update(float time);
	Sprite getLineSprite(int i);
	bool getState();
};