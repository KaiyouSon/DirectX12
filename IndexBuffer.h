#pragma once
#include <d3d12.h>
#include <stdint.h>

class IndexBuffer
{
private:
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView{};
public:
	void Initialize(uint16_t indices[], int arrarySize);
public:
	// インデックスバッファビューを取得する関数
	D3D12_INDEX_BUFFER_VIEW* GetibViewAddress();

};

