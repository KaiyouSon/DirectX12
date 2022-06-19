#include "Header/GraphicsPipeline3D.h"
#include "Header/ShaderCompiler.h"
#include "Header/NewEngineBase.h"
#include "Header/RootSignature.h"
#include <cassert>
using namespace Microsoft::WRL;

void GraphicsPipeline3D::Initialize()
{
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode =
		ShaderCompiler::GetInstance()->GetvsBlob()->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength =
		ShaderCompiler::GetInstance()->GetvsBlob()->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode =
		ShaderCompiler::GetInstance()->GetpsBlob()->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength =
		ShaderCompiler::GetInstance()->GetpsBlob()->GetBufferSize();

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// 背面をカリング
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// デプスステンシルステートの設定
	pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テストを行う
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;	// 書き込み許可
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;	// 小さいほうを採用
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット

	// ブレンドステート
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask =
	//	D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blenddesc.BlendEnable = true;					// ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	// 加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		// ソースの値を100％使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	// デストの値を  0％使う

	// 加算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;	// 加算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;		// ソースの値を100％使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;	// デストの値を100％使う

	// 減算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;	// デストからソースを減算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;				// ソースの値を100％使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;			// デストの値を100％使う

	// 色反転
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;		// 1.0f-デストカラーの値
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;				// 使わない

	// 半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;				// 加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			// ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;		// 1.0f-ソースのアルファ値

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs =
		ShaderCompiler::GetInstance()->GetInputLayout();
	pipelineDesc.InputLayout.NumElements =
		ShaderCompiler::GetInstance()->GetInputLayoutSize();

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0～255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = RootSignature::GetInstance()->GetRootSignature().Get();

	HRESULT result;

	// パイプランステートの生成
	result = NewEngineBase::GetInstance()->GetDevice()->
		CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

ComPtr<ID3D12PipelineState>GraphicsPipeline3D::GetPipelineState()
{
	return pipelineState;
}

GraphicsPipeline3D* GraphicsPipeline3D::GetInstance()
{
	static GraphicsPipeline3D* graphicsPipeline = new GraphicsPipeline3D;
	return graphicsPipeline;
}

void GraphicsPipeline3D::DestroyInstance()
{
	delete GraphicsPipeline3D::GetInstance();
}
