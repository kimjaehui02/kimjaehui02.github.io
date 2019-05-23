#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen
{
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1])
	{
		printf("Screen constructor\n");
	}
	~Screen()
	{
		printf("Screen destructor\n");
		if(screen)
		{
			delete[] screen;
			screen = nullptr;
		}
	}

	void draw(int pos, const char* face)
	{
		if(face == nullptr) return;
		if(pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render()
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject
{
	int pos;
	char face[20];
	Screen* screen;

public:
	GameObject(int pos, const char* face, Screen* screen)
		: pos(pos), screen(screen)
	{
		printf("GameObject constructor\n");
		strcpy(this->face, face);
	}

	~GameObject()
	{
		printf("GameObject destructor\n");
	}


	int getPosition()
	{
		return pos;
	}
	void setPosition(int pos)
	{
		this->pos = pos;
	}
	void draw()
	{
		screen->draw(pos, face);
	}

	virtual void moveLeft()
	{
	}

	virtual void moveRight()
	{
	}

	virtual void update()
	{
	}

	virtual void update(int enemy_pos)
	{
	}
	virtual void fire(int player_pos){ }
};

class Player : public GameObject
{

public:
	Player(int pos, const char* face, Screen* screen)
		: GameObject(pos, face, screen)
	{
		printf("Player constructor\n");
	}

	~Player()
	{
		printf("Player destructor\n");
	}


	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void update()
	{

	}

};

class Enemy : public GameObject
{

public:
	Enemy(int pos, const char* face, Screen* screen)
		: GameObject(pos, face, screen)
	{
		printf("Enemy constructor\n");
	}

	~Enemy()
	{
		printf("Enemy destructor\n");
	}

	void moveRandom()
	{
		setPosition(getPosition() + rand() % 3 - 1);
	}

	void update()
	{
		moveRandom();
	}
};

class Bullet : public GameObject
{
	bool isFiring;

public:
	Bullet(int pos, const char* face, Screen* screen)
		: GameObject(pos, face, screen), isFiring(false)
	{
		printf("Bullet constructor\n");
	}
	~Bullet()
	{
		printf("Bullet destructor\n");
	}

	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void draw()
	{
		if(isFiring == false) return;
		GameObject::draw();
	}

	void fire(int player_pos)
	{
		isFiring = true;
		setPosition(player_pos);
	}

	void update(int enemy_pos)
	{
		if(isFiring == false) return;
		int pos = getPosition();
		if(pos < enemy_pos)
		{
			pos = pos + 1;
		}
		else if(pos > enemy_pos)
		{
			pos = pos - 1;
		}
		else
		{
			isFiring = false;
		}
		setPosition(pos);
	}
};

#define NORMAL_PLAY 1

#if NORMAL_PLAY
int main()
{
	Screen one{ 80 };

	Screen &screen = one;

	GameObject* AO[3];

	AO[0] = new Player({ 30, "(^_^)", &screen });

	AO[1] = new Enemy({ 60, "(*--*)", &screen });

	AO[2] = new Bullet({ -1, "+", &screen });

	//GameObject AllO[3]{ {30, "(^_^)", &screen },
	//					{ 60, "(*--*)", &screen },
	//					{-1, "+", &screen} };

	//Player player = { 30, "(^_^)", &screen };
	//Enemy enemy{ 60, "(*--*)", &screen };
	//Bullet bullet(-1, "+", &screen);

	while(true)
	{
		screen.clear();

		if(_kbhit())
		{
			int c = _getch();
			switch(c)
			{
			case 'a':
				AO[0]->moveLeft();
				break;
			case 'd':
				AO[0]->moveRight();
				break;
			case ' ':
				AO[2]->fire(AO[0]->getPosition());
				break;
			}
		}
		AO[0]->draw();
		AO[1]->draw();
		AO[2]->draw();

		AO[0]->update();
		AO[1]->update();
		AO[2]->update(AO[1]->getPosition());

		screen.render();
		Sleep(66);
	}

	return 0;
}
#else

void test()
{
	Screen* screen = nullptr;

	screen = new Screen(80);
	/* 80 };
	Player player = { 30, "(^_^)", &screen };
	Enemy enemy{ 60, "(*--*)", &screen };
	Bullet bullet(-1, "+", &screen);
	*/

}

int main()
{
	test();


	Screen* another = nullptr;
	int ch = _getch();
	return 0;
}

#endif