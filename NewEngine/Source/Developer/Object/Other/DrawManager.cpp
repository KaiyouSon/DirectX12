#include "NewEngine/Header/Developer/Object/Other/DrawManager.h"
#include "NewEngine/Header/Developer/Component/ModelData.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

Texture* LoadTexture(const char* filePath)
{
	return TextureBuffer::LoadTexture(filePath);
}

ModelData LoadModel(const char* filePath)
{
	// ファイルストリーム
	ifstream file;
	// .objファイルを開く
	file.open(filePath);
	// ファイルオープン失敗をチェック
	//if (file.fail()) assert(0);
	if (file.fail())
	{
		ModelData errorModel;
		errorModel.SetTag("error");
		return errorModel;
	}

	ModelData modelData;
	vector<Vec3> positions;
	vector<Vec3> normals;
	vector<Vec2> texcoords;

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
		}

		// 先頭文字列がvtならテクスチャ
		if (key == "vt")
		{
			// uv成分読み込み
			Vec2 texcoord{};
			lineStream >> texcoord.x;
			lineStream >> texcoord.y;
			// v方向反転
			texcoord.y = 1.0f - texcoord.y;
			// テクスチャ座標データに追加
			texcoords.emplace_back(texcoord);
		}

		// 先頭文字列がvnなら法線ベクトル
		if (key == "vn")
		{
			// xyz成分読み込み
			Vec3 normal{};
			lineStream >> normal.x;
			lineStream >> normal.y;
			lineStream >> normal.z;
			// 法線ベクトルデータに追加
			normals.emplace_back(normal);
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
				unsigned short indexPos, indexNormal, indexTexcoord;
				indexStream >> indexPos;
				indexStream.seekg(1, ios_base::cur);	// スラッシュを飛ばす
				indexStream >> indexTexcoord;
				indexStream.seekg(1, ios_base::cur);	// スラッシュを飛ばす
				indexStream >> indexNormal;
				// 頂点データの追加
				Vertex vertex{};
				vertex.pos = positions[indexPos - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				modelData.vertices.emplace_back(vertex);

				// 頂点インデックスに追加
				modelData.indices.emplace_back((unsigned short)modelData.indices.size());
			}
		}
	}

	// ファイルを閉じる
	file.close();

	// ファイルパス
	modelData.SetFilePath(filePath);

	return modelData;
}
void UnLoadTexture(Texture* texture)
{
	TextureBuffer::UnLoadTexture(texture);
}