#include "NewEngine/Header/Developer/Object/Object2D/RenderTexture.h"
#include "NewEngine/Header/Developer/Object/Other/ViewProjection.h"
#include "NewEngine/Header/Render/RenderBase.h"
#include "NewEngine/Header/Render/RenderWindow.h"

const float RenderTexture::clearColor[4] = { 0.25f,0.5f,0.1f,1.0f };

RenderTexture::RenderTexture() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer), size(0, 0)
{
}

RenderTexture::~RenderTexture()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void RenderTexture::Initialize(Vec2 size)
{
	HRESULT result;

	// ���_�f�[�^
	vertices.push_back({ { -(size.x / 2), +(size.y / 2), 0.0f },{}, {0.0f, 1.0f} });	//����
	vertices.push_back({ { -(size.x / 2), -(size.y / 2), 0.0f },{}, {0.0f, 0.0f} });	//����
	vertices.push_back({ { +(size.x / 2), +(size.y / 2), 0.0f },{}, {1.0f, 1.0f} });	//�E��
	vertices.push_back({ { +(size.x / 2), -(size.y / 2), 0.0f },{}, {1.0f, 0.0f} });	//�E��

	// �O�p�`1��
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	// �O�p�`2��
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	vertexBuffer->Initialize(vertices);
	indexBuffer->Initialize(indices);

	// �萔�o�b�t�@
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	Texture tmpTex = TextureBuffer::GetRenderTexture(
		{
			(float)RenderWindow::GetInstance().GetWinWidth(),
			(float)RenderWindow::GetInstance().GetWinHeight(),
		});
	GetComponent<Texture>()->SetTexture(&tmpTex);

	// RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc = {};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV�p�f�X�N���v�^�q�[�v���쐬
	result = renderBase->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v��RTV�쐬
	renderBase->GetDevice()->CreateRenderTargetView(
		GetComponent<Texture>()->buffer.Get(),
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

void RenderTexture::Update()
{
	GetComponent<Transform>()->Update();

	// �萔�o�b�t�@�ɓ]��
	constantBuffer->constMapTransform->mat =
		GetComponent<Transform>()->matWorld *
		view->matView *
		view->matProjection3D;
}

void RenderTexture::PreDrawScene()
{
	CD3DX12_RESOURCE_BARRIER resourceBarrier;
	resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetComponent<Texture>()->buffer.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	//���\�[�X�o���A��ύX�i�V�F�[�_�[���\�[�X -> �`��\�j
	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier);

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

void RenderTexture::PostDrawScene()
{
	// ���\�[�X�o���A��ύX�i �`��\ -> �V�F�[�_�[���\�[�X�j
	CD3DX12_RESOURCE_BARRIER resourceBarrier;
	resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		GetComponent<Texture>()->buffer.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	renderBase->GetCommandList()->ResourceBarrier(1, &resourceBarrier);
}

void RenderTexture::Draw()
{
	renderBase->GetCommandList()->SetPipelineState(renderBase->pipelineState2D.Get());
	renderBase->GetCommandList()->SetGraphicsRootSignature(renderBase->rootSignature.Get());
	renderBase->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// VBV��IBV�̐ݒ�R�}���h
	renderBase->GetCommandList()->IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	renderBase->GetCommandList()->IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// �}�e���A���ƃg�����X�t�H�[����CBV�̐ݒ�R�}���h
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());
	renderBase->GetCommandList()->SetGraphicsRootConstantBufferView(
		1, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	renderBase->GetCommandList()->SetDescriptorHeaps(1, renderBase->GetSrvDescHeap().GetAddressOf());
	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^2�Ԃɐݒ�
	renderBase->GetCommandList()->SetGraphicsRootDescriptorTable(2, GetComponent<Texture>()->GetGpuHandle());

	renderBase->GetCommandList()->DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}

void RenderTexture::SetTexture(const Texture& texture)
{
	//this->texture = texture;
}

void RenderTexture::SetColor(const Color& color)
{
	// �F�̎w��
	constantBuffer->SetColor(color);
}

void RenderTexture::SetCutPosAndSize(const Vec2& cutPos, const Vec2& cutSize)
{
	//float texLeft = cutPos.x / texture.GetTextureSize().x;
	//float texRight = (cutPos.x + cutSize.x) / texture.GetTextureSize().x;
	//float texUp = cutPos.y / texture.GetTextureSize().y;
	//float texDown = (cutPos.y + cutSize.y) / texture.GetTextureSize().y;

	//vertices[0].uv = { texLeft , texDown };	// ����
	//vertices[1].uv = { texLeft ,   texUp };	// ����
	//vertices[2].uv = { texRight ,texDown }; // �E��
	//vertices[3].uv = { texRight ,  texUp }; // �E��

	//vertexBuffer->TransferToBuffer();
}

Texture RenderTexture::GetRenderTexture()
{
	return *GetComponent<Texture>();
}
