#pragma once
#include "Image.h"
class Cube
{
private:
	Image* image;

	Transform transform;

	Transform forwardTrans;
	Transform backTrans;
	Transform leftTrans;
	Transform rightTrans;
	Transform upTrans;
	Transform downTrans;

public:
	Cube();
	~Cube();
	void LoadGraph(const wchar_t* FilePath = L"void");
	void Initialize();
	void Update(Transform& transform);
	void Draw();
public:
	enum Direction
	{
		Forward,
		Back,
		Left,
		Right,
		Up,
		Down,
	};
};

