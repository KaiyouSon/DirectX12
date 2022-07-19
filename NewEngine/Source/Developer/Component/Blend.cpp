#include "NewEngine/Header/Developer/Component/Blend.h"
#include "NewEngine/Header/Render/RenderBase.h"

void Blend::SetBlendMode(BlendMode blendmode)
{
	switch (blendmode)
	{
	case Alpha3D:
		renderBase->GetCommandList()->SetPipelineState(renderBase->GetPipelineStateAlpha3D().Get());
		renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->GetRootSignature().Get());
		renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;

	case Add3D:
		renderBase->GetCommandList()->SetPipelineState(renderBase->GetPipelineStateAdd3D().Get());
		renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->GetRootSignature().Get());
		renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;

	case Alpha2D:
		renderBase->GetCommandList()->SetPipelineState(renderBase->GetPipelineStateAlpha2D().Get());
		renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->GetRootSignature().Get());
		renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;

	case AddLine:
		renderBase->GetCommandList()->SetPipelineState(renderBase->GetPipelineStateLine().Get());
		renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->GetRootSignature().Get());
		renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	default:
		break;
	}
}