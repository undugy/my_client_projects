#pragma once
#include "header.h"


class Sound {

public:
	FMOD_SYSTEM* soundSystem;   //���� �ý���
	FMOD_SOUND* bgmSound[2];	//����ݰ���
	FMOD_SOUND* effectSound[6];	//����Ʈ��ݰ���
	FMOD_CHANNEL* Channel[2];	//���+����Ʈ �ؼ� ä��

	//���� �ʱ�ȭ �Լ�
	void Init_Sound();


};



