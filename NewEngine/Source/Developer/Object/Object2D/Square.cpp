#include "NewEngine/Header/Developer/Object/Object2D/Square.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"

const float Square::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

Square::Square() :
	vertexBuffer(new VertexBuffer),
	indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer),
	size(0, 0),
	ibArraySize(0), vbArraySize(0), viewType(view2D)
{
}

Square::~Square()
{
	//vertexBuffer->Unmap();

	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Square::Initialize(int viewType, Vec2 size)
{
	this->viewType = viewType;
	this->size = size;

	// ���_�f�[�^
	if (viewType == view2D)
	{
		vertices[0] = { { -(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {0.0f, 1.0f} }; //����
		vertices[1] = { { -(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {0.0f, 0.0f} }; //����
		vertices[2] = { { +(this->size.x / 2), +(this->size.y / 2), 0.0f },{}, {1.0f, 1.0f} }; //�E��
		vertices[3] = { { +(this->size.x / 2), -(this->size.y / 2), 0.0f },{}, {1.0f, 0.0f} }; //�E��
	};
	if (viewType == view3D)
	{
		vertices[0] = { { -0.5f, -0.5f, 0.0f },{},{0.0f, 1.0f} }; //����
		vertices[1] = { { -0.5f, +0.5f, 0.0f },{},{0.0f, 0.0f} }; //����
		vertices[2] = { { +0.5f, -0.5f, 0.0f },{},{1.0f, 1.0f} }; //�E��
		vertices[3] = { { +0.5f, +0.5f, 0.0f },{},{1.0f, 0.0f} }; //�E��
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		0,1,2, // �O�p�`1��
		2,1,3, // �O�p�`2��
	};

	// ���_�f�[�^�̗v�f��
	vbArraySize = sizeof(vertices) / sizeof(vertices[0]);
	// �C���f�b�N�X�̗v�f��
	ibArraySize = sizeof(indices) / sizeof(indices[0]);

	// ���_�o�b�t�@
	vertexBuffer->Initialize(vertices, vbArraySize);
	// �C���f�b�N�X�o�b�t�@
	indexBuffer->Initialize(indices, ibArraySize);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetRenderTexture(
		{
			(float)RenderWindow::GetInstance().GetWinWidth(),
			(float)RenderWindow::GetInstance().GetWinHeight(),
		});

	HRESULT result;
	RenderBase* renderBase = RenderBase::GetInstance();

	//// �e�N�X�`�����\�[�X�ݒ�
	//CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	RenderWindow::GetInstance().GetWinWidth(),
	//	(UINT)RenderWindow::GetInstance().GetWinHeight(),
	//	1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

	//// �e�N�X�`���o�b�t�@�̐���
	//CD3DX12_HEAP_PROPERTIES texHeapProperties =
	//	CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	//CD3DX12_CLEAR_VALUE texClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor);

	//result = renderBase->GetDevice()->CreateCommittedResource(
	//	&texHeapProperties,
	//	D3D12_HEAP_FLAG_NONE,
	//	&texresDesc,
	//	D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
	//	//nullptr,
	//	&texClearValue,
	//	IID_PPV_ARGS(&texBuff));
	//assert(SUCCEEDED(result));

	//// �e�N�X�`����ԃN���A
	//{
	//	// ��f��
	//	const UINT pixelCont =
	//		RenderWindow::GetInstance().GetWinWidth() *
	//		RenderWindow::GetInstance().GetWinHeight();
	//	// �摜�P�s���̃f�[�^�T�C�Y
	//	const UINT rowPitch = sizeof(UINT) * RenderWindow::GetInstance().GetWinWidth();
	//	// �摜�S�̂̃f�[�^�T�C�Y
	//	const UINT depthPitch = rowPitch * RenderWindow::GetInstance().GetWinHeight();
	//	// �摜�C���[�W
	//	UINT* img = new UINT[pixelCont];
	//	for (int i = 0; i < pixelCont; i++) { img[i] = 0xff0000ff; }

	//	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	//	result = texBuff->WriteToSubresource(0, nullptr,
	//		img, rowPitch, depthPitch);
	//	assert(SUCCEEDED(result));
	//	delete[] img;
	//}

	//// SRV�p�f�X�N���v�^�q�[�v�ݒ�
	//D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	//srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//srvDescHeapDesc.NumDescriptors = 1;
	//// SRV�p�f�X�N���v�^�q�[�v���쐬
	//result = renderBase->GetDevice()->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	//assert(SUCCEEDED(result));

	//// SRV�ݒ�
	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// �ݒ�\����
	//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Texture2D.MipLevels = 1;

	//// �f�X�N���v�^�q�[�v��SRV�쐬
	//renderBase->GetDevice()->CreateShaderResourceView(texBuff.Get(),	// �r���[�Ɗ֘A�t����o�b�t�@
	//	&srvDesc,
	//	descHeapSRV->GetCPUDescriptorHandleForHeapStart());

	// RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc = {};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV�p�f�X�N���v�^�q�[�v���쐬
	result = renderBase->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v��RTV�쐬
	renderBase->GetDevice()->CreateRenderTargetView(texture.buffer.Get(),
		//renderBase->GetDevice()->CreateRenderTargetView(texBuff.Get(),
		nullptr,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart());

	// �[�x�o�b�t�@���\�[�X�̐ݒ�
	CD3DX12_RESOURCE_DESC depthRecDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			RenderWindow::GetInstance().GetWinWidth(),
			(UINT)RenderWindow::GetInstance().GetWinHeight(),
			1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	// �[�x�o�b�t�@�̐���
	CD3DX12_HEAP_PROPERTIES depthHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_CLEAR_VALUE depthClearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	result = renderBase->GetDevice()->CreateCommittedResource(
		&depthHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthRecDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	// RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc = {};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	// RTV�p�f�X�N���v�^�q�[�v���쐬
	result = renderBase->GetDevice()->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v�̍쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�n�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	renderBase->GetDevice()->CreateDepthStencilView(depthBuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart());

}

void Square::Update(const Transform& transform, Transform* parent)
{
	this->transform = transform;
	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// �萔�o�b�t�@�ɓ]��
	if (viewType == view2D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			view->matProjection2D;
	}
	if (viewType == view3D)
	{
		constantBuffer->constMapTransform->mat =
			this->transform.matWorld *
			view->matView *
			view->matProjection3D;
	}
}

void Square::PreDrawScene()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	CD3DX12_RESOURCE_BARRIER resourceBarrier1 =
		//CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		CD3DX12_RESOURCE_BARRIER::Transition(texture.buffer.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET);

	//���\�[�X�o���A��ύX�i�V�F�[�_�[���\�[�X -> �`��\�j
	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier1);

	// �����_�[�^�[�Q�b�g�r���[�p�f�B�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH = descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	// �[�x�X�e���V���r���[�p�f�B�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH = descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	// �����_�[�^�[�Q�b�g���Z�b�g
	renderBase->GetCommandList()->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	// �r���[�|�[�g�̐ݒ�
	CD3DX12_VIEWPORT viewport = CD3DX12_VIEWPORT(
		0.0f, 0.0f,
		RenderWindow::GetInstance().GetWinWidth(),
		RenderWindow::GetInstance().GetWinHeight());

	renderBase->GetCommandList()->RSSetViewports(1, &viewport);
	// �V�U�����O��`�̐ݒ�
	CD3DX12_RECT scissorRect = CD3DX12_RECT(
		0, 0,
		RenderWindow::GetInstance().GetWinWidth(),
		RenderWindow::GetInstance().GetWinHeight());

	renderBase->GetCommandList()->RSSetScissorRects(1, &scissorRect);

	// �S��ʃN���A
	renderBase->GetCommandList()->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	// �[�x�o�b�t�@�̃N���A
	renderBase->GetCommandList()->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void Square::PostDrawScene()
{
	// ���\�[�X�o���A��ύX�i �`��\ -> �V�F�[�_�[���\�[�X�j
	CD3DX12_RESOURCE_BARRIER resourceBarrier2 =
		//CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		CD3DX12_RESOURCE_BARRIER::Transition(texture.buffer.Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	RenderBase::GetInstance()->GetCommandList()->
		ResourceBarrier(1, &resourceBarrier2);
}

void Square::Draw()
{
	RenderBase* renderBase = RenderBase::GetInstance();

	renderBase->GetCommandList()->SetPipelineState(renderBase->pipelineState2D.Get());
	renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->rootSignature.Get());
	renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		//SetDescriptorHeaps(1, descHeapSRV.GetAddressOf());
		SetDescriptorHeaps(1, RenderBase::GetInstance()->GetSrvDescHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	renderBase->GetCommandList()->
		//SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());
		SetGraphicsRootDescriptorTable(1, texture.GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	renderBase->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	renderBase->GetCommandList()->
		DrawIndexedInstanced(ibArraySize, 1, 0, 0, 0);
}

void Square::SetTexture(const Texture& texture)
{
	this->texture = texture;
}

void Square::SetColor(const Color& color)
{
	// �F�̎w��
	constantBuffer->SetColor(color);
}

void Square::SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize)
{
	float texLeft = cutPos.x / texture.GetTextureSize().x;
	float texRight = (cutPos.x + cutSize.x) / texture.GetTextureSize().x;
	float texUp = cutPos.y / texture.GetTextureSize().y;
	float texDown = (cutPos.y + cutSize.y) / texture.GetTextureSize().y;

	vertices[0].uv = { texLeft , texDown };	// ����
	vertices[1].uv = { texLeft ,   texUp };	// ����
	vertices[2].uv = { texRight ,texDown }; // �E��
	vertices[3].uv = { texRight ,  texUp }; // �E��

	vertexBuffer->TransferToBuffer();
}

Texture Square::GetRenderTexture()
{
	return texture;
}
