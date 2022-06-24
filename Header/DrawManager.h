#pragma once
#include "Header/Square.h"
#include "Header/Cube.h"
#include "Header/Object3D.h"
#include "Header/TextureBuffer.h"

// テクスチャーの読み込み
Texture LoadTexture(const char* filePath);
// モデルの読み込み
ModelData LoadModel(const char* filePath);

extern Model cube;
extern Model sphere;
extern Model monkey;
void LoadBasicModel();