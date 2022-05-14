#include "Cube.h"
#include "MathUtil.h"

Cube::Cube() : image(new Image[6])
{
}

Cube::~Cube()
{
	delete[] image;
}

void Cube::LoadGraph(const wchar_t* FilePath)
{
	for (int i = 0; i < 6; i++)
	{
		image[i].LoadGraph(FilePath);
	}
}

void Cube::Initialize()
{
	for (int i = 0; i < 6; i++)
	{
		image[i].Initialize(Image::view3D);
	}
}

void Cube::Update(Transform& transform)
{
	this->transform = transform;
	this->transform.Update();

	forwardTrans.pos = { 0, 0, -2.5 };
	forwardTrans.scale = { 1, 1, 1 };
	forwardTrans.rot = { 0,0,0 };

	backTrans.pos = { 0, 0, 2.5 };
	backTrans.scale = { 1, 1, 1 };
	backTrans.rot = { 0,180,0 };

	leftTrans.pos = { -2.5,0,0 };
	leftTrans.scale = { 1,1,1 };
	leftTrans.rot = { 0,90,0 };

	rightTrans.pos = { 2.5,0,0 };
	rightTrans.scale = { 1,1,1 };
	rightTrans.rot = { 0,270,0 };

	upTrans.pos = { 0,2.5,0 };
	upTrans.scale = { 1,1,1 };
	upTrans.rot = { 90,0,0 };

	downTrans.pos = { 0,-2.5,0 };
	downTrans.scale = { 1,1,1 };
	downTrans.rot = { 270,0,0 };

	image[Direction::Forward].Update(forwardTrans, &this->transform);
	image[Direction::Back].Update(backTrans, &this->transform);
	image[Direction::Left].Update(leftTrans, &this->transform);
	image[Direction::Right].Update(rightTrans, &this->transform);
	image[Direction::Up].Update(upTrans, &this->transform);
	image[Direction::Down].Update(downTrans, &this->transform);
}

void Cube::Draw()
{
	for (int i = 0; i < 6; i++)
		image[i].Draw();
}