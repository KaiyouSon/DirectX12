#pragma once
#include <wrl.h>
#include <fstream>
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

// �`�����N�w�b�_
struct ChunkHeader
{
	char id[4];		// �`�����N����ID
	int32_t size;	// �`�����N�T�C�Y
};

// RIFF�w�b�_�`�����N
struct RiffHeader
{
	ChunkHeader chunk;	// "RIFF"
	char type[4];	// "WAVE"
};

// FMT�`�����N
struct FormatChunk
{
	ChunkHeader chunk;	// "fmt"
	WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
};

// �����f�[�^
struct SoundData
{
	// �g�`�t�H�[�}�b�g
	WAVEFORMATEX wfex;
	// �o�b�t�@�̐擪�A�h���X
	BYTE* pBuffer;
	// �o�b�t�@�̃T�C�Y
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