#pragma once
#include "Square.h"
class Cube
{
private:
	Square* square;

public:
	Cube();
	~Cube();
	void Initialize();
	void Update(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT4 color);
	void Draw();
};

