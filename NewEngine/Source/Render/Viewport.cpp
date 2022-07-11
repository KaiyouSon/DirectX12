#include "NewEngine/Header/Render/Viewport.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"
#include "NewEngine/Header/Gui/SceneLayer.h"
#include <memory>

std::unique_ptr<Viewport> viewport(new Viewport);

void Viewport::Update()
{
	//----------------------- �r���[�|�[�g�̐ݒ�R�}���h -----------------------//
	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = leftTopPos.x;
	viewport.TopLeftY = leftTopPos.y;
	viewport.Width = size.x;
	viewport.Height = size.y;
	viewport.MinDepth = MinDepth;
	viewport.MaxDepth = MaxDepth;

	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	RenderBase::GetInstance()->GetCommandList()->RSSetViewports(1, &viewport);
}

void Viewport::SetViewport(const Vec2& leftTopPos, const Vec2& size, float MinDepth, float MaxDepth)
{
	this->leftTopPos = leftTopPos;
	this->size = size;
	this->MinDepth = MinDepth;
	this->MaxDepth = MaxDepth;
}

Vec2 Viewport::GetLeftTopPos() { return leftTopPos; }
Vec2 Viewport::GetSize() { return size; }
float Viewport::GetMinDepth() { return MinDepth; }
float Viewport::GetMaxDepth() { return MaxDepth; }
