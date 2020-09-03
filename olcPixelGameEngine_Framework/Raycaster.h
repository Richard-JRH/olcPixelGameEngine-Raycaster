#ifndef _Raycaster_H_
#define _Raycaster_H_

#include "olcPixelGameEngine.h"
#include <math.h>

class Raycaster : public olc::PixelGameEngine
{
private:	// Constants
	const float		 PI = 3.141592653589793238462f;

	static const int MAP_WIDTH = 20;
	static const int MAP_HEIGHT = 15;

	const float		 TURN_SPEED = 1.5f;
	static const int SPEED = 100;
	static const int SIZE = 12;

	static const int FOV = 80;
	static const int NUM_RAYS = 800;

	const olc::Pixel PLAYER_COLOUR = olc::GREEN;
	const olc::Pixel RAY_COLOUR = olc::RED;
	const olc::Pixel WALL_COLOUR = olc::GREY;
	const olc::Pixel FLOOR_COLOUR = olc::DARK_BLUE;
private:
	int W, H;						 // Screen coords
	int blockWidth, blockHeight;	 // Block Dimensions
	int Map[MAP_WIDTH][MAP_HEIGHT];	 // Map Dimensions

	bool firstPersonMode;
private:
	struct Vec2
	{
		int x, y;
		Vec2()				 : x(0),  y(0)  {}
		Vec2(int _x, int _y) : x(_x), y(_y) {}
	};

	struct Player 
	{
		Vec2 pos;
		int size;
		float theta;

		Player() : pos(0, 0), size(0), theta(0) {}
	} player;
public:
	Raycaster();
	~Raycaster();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);
	void Render(const float& dt);
public:
	void InitMap();
	void DrawMap();

	void DrawPlayer();
	void DrawRays();
	void RenderScene();
	olc::Pixel interpColour( float dist );

	void InputHandler(const float &dt);
	void Constrain();
};

#endif

