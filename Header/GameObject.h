#pragma once
#include "Header/Transform.h"

class GameObject
{
protected:
	Transform transform;

public:
	GameObject();
	~GameObject();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};