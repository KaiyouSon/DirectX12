#include "GraphicsCommand.h"
#include "NewEngineBase.h"
#include "GraphicsPipeline.h"
#include "Viewport.h"
#include "ScissorRectangle.h"
#include "DepthBuffer.h"
#include <cassert>

extern GraphicsPipeline* graphicsPipeline;
Viewport* viewport = new Viewport;
ScissorRectangle* scissorRectangle = new ScissorRectangle;

GraphicsCommand::~GraphicsCommand()
{
	delete viewport;
	delete scissorRectangle;
}

void GraphicsCommand::PreUpdate()
{
	//---------------------- リソースバリアの変更コマンド ----------------------//
	// バックバッファの番号を取得（2つなので0番か1番）
	UINT bbIndex = NewEngineBase::GetInstance().GetSwapChain()->GetCurrentBackBufferIndex();
	// １．リソースバリアで書き込み可能に変更
	barrierDesc.Transition.pResource =
		NewEngineBase::GetInstance().GetBackBuffers()[bbIndex]; // バックバッファを指定
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // 表示状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態へ
	NewEngineBase::GetInstance().GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//--------------------------- 描画先指定コマンド ---------------------------//
	// ２．描画先の変更
	// レンダーターゲットビューのハンドルを取得
	rtvHandle = NewEngineBase::GetInstance().
		GetRTVHeap()->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * NewEngineBase::GetInstance().GetDevice()->
		GetDescriptorHandleIncrementSize(
			NewEngineBase::GetInstance().GetRTVHeapDesc().Type);
	
	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle =DepthBuffer::GetInstance().
		GetDsvHeap()->GetCPUDescriptorHandleForHeapStart();
	NewEngineBase::GetInstance().GetCommandList()->
		OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 画面クリア R G B A
	NewEngineBase::GetInstance().GetCommandList()->
		ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	// 深度バッファクリア
	NewEngineBase::GetInstance().GetCommandList()->
		ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	// ビューポートの処理
	viewport->Update();

	// シザー矩形の処理
	scissorRectangle->Update();

	//---------- パイプラインステートとルートシグネチャの設定コマンド ----------//
	// パイプラインステートとルートシグネチャの設定コマンド
	NewEngineBase::GetInstance().GetCommandList()->
		SetPipelineState(graphicsPipeline->GetPipelineState());
	NewEngineBase::GetInstance().GetCommandList()->
		SetGraphicsRootSignature(graphicsPipeline->GetRootSignature());
}


void GraphicsCommand::PostUpdate()
{
	//---------------------- リソースバリアの復帰コマンド ----------------------//
	// ５．リソースバリアを戻す
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // 描画状態から
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // 表示状態へ
	NewEngineBase::GetInstance().GetCommandList()->ResourceBarrier(1, &barrierDesc);

	//-------------------------- コマンドのフラッシュ --------------------------//
	// 命令のクローズ
	result = NewEngineBase::GetInstance().GetCommandList()->Close();
	assert(SUCCEEDED(result));
	// コマンドリストの実行
	ID3D12CommandList* commandLists[] = { NewEngineBase::GetInstance().GetCommandList() };
	NewEngineBase::GetInstance().GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// 画面に表示するバッファをフリップ（裏表の入替え）
	result = NewEngineBase::GetInstance().GetSwapChain()->Present(1, 0);
	assert(SUCCEEDED(result));

	//---------------------------- コマンド完了待ち ----------------------------//
	// コマンドの実行完了を待つ
	NewEngineBase::GetInstance().GetCommandQueue()->Signal(
		NewEngineBase::GetInstance().GetFence(), NewEngineBase::GetInstance().PreIncreFenceVal());
	if (NewEngineBase::GetInstance().GetFence()->GetCompletedValue() !=
		NewEngineBase::GetInstance().GetFenceVal())
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		NewEngineBase::GetInstance().GetFence()->SetEventOnCompletion(
			NewEngineBase::GetInstance().GetFenceVal(), event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	// キューをクリア
	result = NewEngineBase::GetInstance().GetCommandAllocataor()->Reset();
	assert(SUCCEEDED(result));
	// 再びコマンドリストを貯める準備
	result = NewEngineBase::GetInstance().GetCommandList()->
		Reset(NewEngineBase::GetInstance().GetCommandAllocataor(), nullptr);
	assert(SUCCEEDED(result));
}

void GraphicsCommand::SetBackgroundColor(float Red, float Green, float Blue)
{
	clearColor[0] = Red / 255;
	clearColor[1] = Green / 255;
	clearColor[2] = Blue / 255;
}