#include "Cube.h"
#include <stdlib.h>

const float PI = 3.1415926;

Cube::Cube() : square(new Square[6])
{
}

Cube::~Cube()
{
	delete square;
}

void Cube::Initialize()
{
	for (int i = 0; i < 6; i++)
	{
		square[i].Initialize();
	}
}

void Cube::Update(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT4 color)
{
	square[0].Update(pos, scale, XMFLOAT3(0, 0, 0), color);
	square[1].Update(pos, scale, XMFLOAT3(0, PI / 2, 0), color);
	square[2].Update(pos, scale, XMFLOAT3(0, PI / 2, 0), color);
	square[3].Update(pos, scale, XMFLOAT3(0, 0, 0), color);
	square[4].Update(pos, scale, XMFLOAT3(0, 0, PI / 2), color);
	square[5].Update(pos, scale, XMFLOAT3(0, 0, PI / 2), color);
}

void Cube::Draw()
{
	for (int i = 0; i < 6; i++)
	{
		square[i].Draw();
	}
}