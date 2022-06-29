#pragma once
#include "NewEngine/Header/Developer/Object/Object3D/Cube.h"
#include "NewEngine/Header/Developer/Object/Object3D/Object3D.h"
#include "NewEngine/Header/Developer/Object/Object2D/Square.h"
#include "NewEngine/Header/Render/Buffer/TextureBuffer.h"

// テクスチャーの読み込み
Texture* LoadTexture(const char* filePath);
// モデルの読み込み
ModelData LoadModel(const char* filePath);

void UnLoadTexture(Texture* texture);

extern Model cube;
extern Model sphere;
extern Model monkey;
void LoadBasicModel();