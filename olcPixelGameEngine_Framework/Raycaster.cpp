#include "Raycaster.h"

Raycaster::Raycaster()
{
}

Raycaster::~Raycaster()
{
}

bool Raycaster::OnUserCreate()
{
	// Init vars
	W = ScreenWidth();
	H = ScreenHeight();

	blockWidth = W / MAP_WIDTH;
	blockHeight = H / MAP_HEIGHT;

	firstPersonMode = false;

	// Init player stats
	player.pos = Vec2( W / 2, H / 2 );
	player.size = SIZE;

	InitMap();

	return true;
}

bool Raycaster::OnUserUpdate(float dt)
{
	InputHandler( dt );
	Render( dt );
	Constrain();

	player.theta += TURN_SPEED * dt;

	if (player.theta > 2 * PI)
		player.theta -= 2 * PI;

	return true;
}

void Raycaster::Render(const float& dt)
{
	Clear( olc::BLACK );

	if ( firstPersonMode )
	{
		// Render in first person view
		RenderScene();
	}
	else
	{
		// Render in top-down, 2D view
		DrawMap();
		DrawPlayer();
		DrawRays();
	}
}

void Raycaster::InitMap()
{
	for (int y = 0; y < MAP_HEIGHT; ++y)
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			if (x == 0 || x == MAP_WIDTH - 1 ||
				y == 0 || y == MAP_HEIGHT - 1)
				Map[x][y] = 1;
			else
				Map[x][y] = 0;
		}

	// Hardcoded stuffs
	Map[1][3] = 1;
	Map[4][3] = 1;
	Map[3][3] = 1;
	Map[5][8] = 1;
	Map[3][12] = 1;
	Map[8][12] = 1;
	Map[9][12] = 1;
	Map[1][12] = 1;
	Map[2][12] = 1;
	Map[1][13] = 1;
	Map[2][13] = 1;
	Map[14][2] = 1;
	Map[14][3] = 1;
	Map[14][4] = 1;
	Map[15][11] = 1;
	Map[16][11] = 1;
	Map[17][11] = 1;
	Map[18][10] = 1;
	Map[18][11] = 1;
}

void Raycaster::DrawMap()
{
	// Draw Map + Grid Lines
	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		for (int x = 0; x < MAP_WIDTH; ++x)
		{
			olc::Pixel colour = (Map[x][y] == 1 ? olc::GREY : olc::BLACK);

			FillRect(x * blockWidth, y * blockHeight, blockWidth, blockHeight, colour);
			DrawLine(x * blockWidth, 0, x * blockWidth, H, olc::VERY_DARK_GREY);
		}

		DrawLine(0, y * blockHeight, W, y * blockHeight, olc::VERY_DARK_GREY);
	}
}

void Raycaster::DrawPlayer()
{
	FillCircle( player.pos.x, player.pos.y, player.size, PLAYER_COLOUR );
}

void Raycaster::DrawRays()
{
	// Player angle in degrees
	float pAngle = player.theta * ( 180.f / PI );

	float startAngle = pAngle - FOV / 2;
	float endAngle = pAngle + FOV / 2;

	float increment = (float)FOV / (float)NUM_RAYS;

	for (float i = startAngle; i < endAngle; i += increment)
	{
		// Deg to rad
		float rayAngle = i * (PI / 180.f);

		// X and Y components of ray
		float rx = cosf( rayAngle );
		float ry = sinf( rayAngle );

		for (float dist = 0.f; dist < FLT_MAX; dist += 1)
		{
			int testX = static_cast<int>(player.pos.x + (rx * dist));
			int testY = static_cast<int>(player.pos.y + (ry * dist));

			testX /= blockWidth;
			testY /= blockHeight;

			if (Map[testX][testY] == 1)
			{
				DrawLine(player.pos.x,
						 player.pos.y,
						 player.pos.x + rx * dist,
						 player.pos.y + ry * dist,
						 RAY_COLOUR);
				break;
			}
		}
	}
}

void Raycaster::InputHandler(const float &dt)
{
	// Move forward
	if ( GetKey(olc::Key::W).bHeld )	
	{
		// X and Y component of player's angle
		float dx = cosf( player.theta );
		float dy = sinf( player.theta );

		player.pos.x += dx * SPEED * dt;
		player.pos.y += dy * SPEED * dt;
	}
	// Turn left
	if ( GetKey(olc::Key::A).bHeld )
	{
		player.theta -= TURN_SPEED * dt;

		if (player.theta < 0)
			player.theta += 2 * PI;
	}
	// Move backward
	if ( GetKey(olc::Key::S).bHeld )
	{
		// X and Y component of player's angle
		float dx = cosf( player.theta );
		float dy = sinf( player.theta );

		player.pos.x -= dx * SPEED * dt;
		player.pos.y -= dy * SPEED * dt;
	}
	// Turn right
	if ( GetKey(olc::Key::D).bHeld )
	{
		player.theta += TURN_SPEED * dt;

		if (player.theta > 2 * PI)
			player.theta -= 2 * PI;
	}

	// Toggle first person mode
	if (GetKey(olc::Key::M).bPressed)
		firstPersonMode = !firstPersonMode;
}

void Raycaster::Constrain()
{
	// World bounds checking
	if ( player.pos.x < 0 )				 player.pos.x = 0;
	if ( player.pos.x > W - player.size) player.pos.x = W - player.size;
	if ( player.pos.y < 0 )				 player.pos.y = 0;
	if ( player.pos.y > H - player.size) player.pos.y = H - player.size;
}

void Raycaster::RenderScene()
{
	// Player angle in degrees
	float pAngle = player.theta * (180.f / PI);

	float startAngle = pAngle - FOV / 2;
	float endAngle = pAngle + FOV / 2;

	float increment = (float)FOV / (float)NUM_RAYS;

	std::vector<float> distVals;

	for (float i = startAngle; i < endAngle; i += increment)
	{
		// Deg to rad
		float rayAngle = i * (PI / 180.f);

		// X and Y components of ray
		float rx = cosf( rayAngle );
		float ry = sinf( rayAngle );

		for (float dist = 0.f; dist < FLT_MAX; dist += 1)
		{
			int testX = static_cast<int>(player.pos.x + (rx * dist));
			int testY = static_cast<int>(player.pos.y + (ry * dist));

			testX /= blockWidth;
			testY /= blockHeight;

			// If ray hit
			if (Map[testX][testY] == 1)
			{
				// Ray scaled by distance
				rx *= dist;
				ry *= dist;

				// X and Y component of player's direction
				float px = cosf( player.theta );
				float py = sinf( player.theta );

				// Calculate dist by projecting rayDir onto playerDir
				float rayProj = ( rx * px + ry * py );

				distVals.push_back( rayProj );
				break;
			}
		}
	}

	// Render Scene
	FillRect( 0, H / 2, W, H, FLOOR_COLOUR);

	for (int i = 0; i < distVals.size(); ++i)
	{
		/*	
			Wall height inverse proportional to distance from wall
			Height = K / Dist
		*/
		float rectHeight = (30'000.f / distVals[i]);

		// Interpolate colour
		olc::Pixel wallColour = interpColour( rectHeight );
		DrawLine( i, (H/2) + rectHeight / 2, i, (H/2) - rectHeight / 2, wallColour );
	}
}

olc::Pixel Raycaster::interpColour( float dist )
{
	int R, G, B;

	olc::Pixel colour1 = olc::BLACK;
	olc::Pixel colour2 = olc::WHITE;

	int maxDist = ScreenHeight() / 2;
	int minDist = 10;

	float dr = colour2.r - colour1.r;
	float dg = colour2.g - colour1.g;
	float db = colour2.b - colour1.b;

	R = dr * (dist / maxDist) + colour1.r;
	G = dg * (dist / maxDist) + colour1.g;
	B = db * (dist / maxDist) + colour1.b;
 
	return olc::Pixel(R, G, B);
}



