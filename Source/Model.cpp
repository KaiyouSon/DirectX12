#include "Header/Model.h"
#include "Header/Vertex.h"
#include "Header/NewEngineBase.h"
#include "Header/ShaderResourceView.h"
#include "Header/ViewProjection.h"
#include "Header/MathUtil.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

vector<Vertex> Model::vertices;
vector<unsigned short> Model::indices;

Model::Model() :
	vertexBuffer(new VertexBuffer), indexBuffer(new IndexBuffer),
	constantBuffer(new ConstantBuffer)
{
}

Model::~Model()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void Model::Load()
{
	// ファイルストリーム
	ifstream file;
	// .objファイルを開く
	file.open("NewEngine/BasicModel/Triangle.obj");
	// ファイルオープン失敗をチェック
	if (file.fail()) assert(0);

	vector<Vec3> positions;
	vector<Vec3> normals;
	vector<Vec3> texcoords;

	// 1行ずつ読み込む
	string line;
	while (getline(file, line))
	{
		// 1行分の文字列をストリームに変換して解析しやすくする
		istringstream lineStream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		string key;
		getline(lineStream, key, ' ');

		// 先頭文字列がvなら頂点座標
		if (key == "v")
		{
			// X,Y,Z座標読み込み
			Vec3 pos{};
			lineStream >> pos.x;
			lineStream >> pos.y;
			lineStream >> pos.z;
			// 座標データに追加
			positions.emplace_back(pos);
			// 頂点データに追加
			Vertex vertex{};
			vertex.pos = pos;
			vertices.emplace_back(vertex);
		}

		// 先頭文字列がfならポリゴン(三角形)
		if (key == "f")
		{
			// 半角スペース区切りで行の続きを読み込む
			string indexString;
			while (getline(lineStream, indexString, ' '))
			{
				// 頂点インデックス1個分の文字列をストリームに変換して解析しやすくする
				istringstream indexStream(indexString);
				unsigned short indexPos;
				indexStream >> indexPos;
				// 頂点インデックスに追加
				indices.emplace_back(indexPos - 1);
			}
		}
	}

	// 頂点バッファ
	vertexBuffer->Initialize(vertices);
	// インデックスバッファ
	indexBuffer->Initialize(indices);

	// ファイルを閉じる
	file.close();

	// 定数バッファ
	constantBuffer->MaterialBufferInit();
	constantBuffer->TransformBufferInit();

	texture = TextureBuffer::GetDefaultTexture();
}

void Model::Update(Transform& transform, Transform* parent)
{
	this->transform = transform;
	this->transform.Update();

	if (parent != nullptr)
	{
		this->transform.matWorld *= parent->matWorld;
	}

	// 定数バッファに転送
	constantBuffer->constMapTransform->mat =
		this->transform.matWorld *
		view->matView *
		view->matProjection3D;
}

void Model::Draw()
{
	// プリミティブ形状の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetVertexBuffers(0, 1, vertexBuffer->GetvbViewAddress());
	// インデックスバッファビューの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		IASetIndexBuffer(indexBuffer->GetibViewAddress());

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			0, constantBuffer->GetConstBuffMaterial()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetDescriptorHeaps(1,
			ShaderResourceView::GetInstance()->GetSrvHeap().GetAddressOf());
	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootDescriptorTable(1, texture.GetGpuHandle());

	// 定数バッファビュー(CBV)の設定コマンド
	NewEngineBase::GetInstance()->GetCommandList()->
		SetGraphicsRootConstantBufferView(
			2, constantBuffer->GetConstBuffTransform()->GetGPUVirtualAddress());

	NewEngineBase::GetInstance()->GetCommandList()->
		DrawIndexedInstanced((unsigned short)indices.size(), 1, 0, 0, 0);
}
