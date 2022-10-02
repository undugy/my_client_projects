#include "Header/Sound.h"


void Sound::Init_Sound()
{
	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 10, FMOD_INIT_NORMAL, NULL);

	//��� �ݺ����
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/bgm.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound[0]);
	//��ī��
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Pikachu.wav", FMOD_DEFAULT, 0, &effectSound[0]);
	//����
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Venonat.wav", FMOD_DEFAULT, 0, &effectSound[1]);
	//�����
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Voltorb.wav", FMOD_DEFAULT, 0, &effectSound[2]);
	//����
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Magnemite.wav", FMOD_DEFAULT, 0, &effectSound[3]);
	//��ì��
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Poliwag.wav", FMOD_DEFAULT, 0, &effectSound[4]);
	//����
	FMOD_System_CreateSound(soundSystem, "Resource/Sound/Gengar.wav", FMOD_DEFAULT, 0, &effectSound[5]);
}
