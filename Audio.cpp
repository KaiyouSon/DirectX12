#include "Audio.h"
#include <cassert>

void Audio::Initialize()
{
	HRESULT result;

	// XAudio�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);

}

SoundData LoadSoundWave(const char* filePath)
{
	// �t�@�C�����̓X�g���[���̃C���X�^���X
	std::ifstream file;
	// .wav�t�@�C�����o�C�i�����[�h�ŊJ��
	file.open(filePath, std::ios_base::binary);
	// �t�@�C���I�[�v�����s�����o
	assert(file.is_open());

	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)	assert(0);
	// �^�C�v��WAVE���`�F�b�N
	if (strncmp(riff.type, "WAVE", 4) != 0) assert(0);

	// Format�`�����N�̓ǂݍ���
	FormatChunk format = {};
	file.read((char*)&format, sizeof(ChunkHeader));
	// �`�����N�w�b�_�[�̊m�F
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) assert(0);
	// �`�����N�{�̂̓ǂݍ���
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNK�`�����N�����������ꍇ
	if (strncmp(data.id, "JUNK ", 4) == 0)
	{
		// �ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size, std::ios_base::cur);
		// �ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data ", 4) != 0) assert(0);

	// Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
	char* pBuffer = new char{ (char)data.size };
	file.read(pBuffer, data.size);

	// wave�t�@�C�������
	file.close();

	// return���邽�߂̉����f�[�^
	SoundData soundData = {};
	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	return soundData;
}

void PlaySoundWave(IXAudio2* xAudio2, const SoundData& soundData)
{
	HRESULT result;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = soundData.pBuffer;
	buffer.AudioBytes = soundData.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	result = pSourceVoice->SubmitSourceBuffer(&buffer);
	result = pSourceVoice->Start();
}

void UnLoadSoundWave(SoundData* soundData)
{
	// �o�b�t�@�̃��������
	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

Audio* Audio::GetInstance()
{
	Audio* audio = new Audio;
	return audio;
}

void Audio::DestroyInstance()
{
	Audio::GetInstance()->xAudio2.Reset();
	delete Audio::GetInstance();
}
