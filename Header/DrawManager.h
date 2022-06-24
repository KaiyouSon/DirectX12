#pragma once
#include "Header/Square.h"
#include "Header/Cube.h"
#include "Header/Object3D.h"
#include "Header/TextureBuffer.h"

// �e�N�X�`���[�̓ǂݍ���
Texture LoadTexture(const char* filePath);
// ���f���̓ǂݍ���
ModelData LoadModel(const char* filePath);

extern Model cube;
extern Model sphere;
extern Model monkey;
void LoadBasicModel();