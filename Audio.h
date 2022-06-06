#pragma once
#include <wrl.h>
#include <fstream>
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

// チャンクヘッダ
struct ChunkHeader
{
	char id[4];		// チャンク毎のID
	int32_t size;	// チャンクサイズ
};

// RIFFヘッダチャンク
struct RiffHeader
{
	ChunkHeader chunk;	// "RIFF"
	char type[4];	// "WAVE"
};

// FMTチャンク
struct FormatChunk
{
	ChunkHeader chunk;	// "fmt"
	WAVEFORMATEX fmt; // 波形フォーマット
};

// 音声データ
struct SoundData
{
	// 波形フォーマット
	WAVEFORMATEX wfex;
	// バッファの先頭アドレス
	BYTE* pBuffer;
	// バッファのサイズ
	unsigned int bufferSize;
};

class Audio
{
private:
	IXAudio2MasteringVoice* masterVoice;

public:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	void Initialize();

	static Audio* GetInstance();
	static void DestroyInstance();
private:
	Audio() = default;
	~Audio() = default;

	Audio(const Audio&) = delete;
	Audio& operator=(const Audio&) = delete;
	Audio(const Audio&&) = delete;
	Audio& operator=(const Audio&&) = delete;
};

SoundData LoadSoundWave(const char* filePath);
void PlaySoundWave(IXAudio2* xaudio2, const SoundData& soundData);
void UnLoadSoundWave(SoundData* soundData);