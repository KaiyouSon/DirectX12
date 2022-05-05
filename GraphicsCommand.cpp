#include "GraphicsCommand.h"
#include "NewEngineBase.h"
#include <cassert>

extern NewEngineBase* newEngine;

void GraphicsCommand::PreUpdate()
{
	//---------------------- リソースバリアの変更コマンド ----------------------//
	// バックバッファの番号を取得（2つなので0番か1番）
	UINT bbIndex = newEngine->GetSwapChain()->GetCurrentBackBufferIndex();
	// １．リソースバリアで書き込み可能に変更
	barrierDesc.Transition.pResource = newEngine->GetBackBuffers()[bbIndex]; // バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // 表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態へ
	newEngine->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//--------------------------- 描画先指定コマンド ---------------------------//
	// ２．描画先の変更
	// レンダーターゲットビューのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = newEngine->GetRTVHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * newEngine->GetDevice()->GetDescriptorHandleIncrementSize(
		newEngine->GetRTVHeapDesc().Type);
	newEngine->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	//--------------------------- 画面クリアコマンド ---------------------------//
	// ３．画面クリア R G B A
	FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f }; // 青っぽい色
	newEngine->GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}


void GraphicsCommand::PostUpdate()
{
	//---------------------- リソースバリアの復帰コマンド ----------------------//
	// ５．リソースバリアを戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // 表示状態へ
	newEngine->GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//-------------------------- コマンドのフラッシュ --------------------------//
	// 命令のクローズ
	result = newEngine->GetCommandList()->Close();
	assert(SUCCEEDED(result));
	// コマンドリストの実行
	ID3D12CommandList* commandLists[] = { newEngine->GetCommandList() };
	newEngine->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ（裏表の入替え）
	result = newEngine->GetSwapChain()->Present(1, 0);
	assert(SUCCEEDED(result));

	//---------------------------- コマンド完了待ち ----------------------------//
	// コマンドの実行完了を待つ
	newEngine->GetCommandQueue()->Signal(newEngine->GetFence(), newEngine->PreIncreFenceVal());
	if (newEngine->GetFence()->GetCompletedValue() != newEngine->GetFenceVal())
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		newEngine->GetFence()->SetEventOnCompletion(newEngine->GetFenceVal(), event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// キューをクリア
	result = newEngine->GetCommandAllocataor()->Reset();
	assert(SUCCEEDED(result));
	// 再びコマンドリストを貯める準備
	result = newEngine->GetCommandList()->Reset(newEngine->GetCommandAllocataor(), nullptr);
	assert(SUCCEEDED(result));
}