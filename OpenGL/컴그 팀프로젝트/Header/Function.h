#pragma once
#include "header.h"
//���� ���̴� ��Ÿ�Լ� ��Ƴ���

//����ȭ�� �÷� �� ��ȯ �Լ�
float NCV(float value);
/*{
	return value / 255.0f;
}*/

//�̸�����, �̸�, ������ġ, Ȯ���ڸ� �����ϸ� Filename�� �����̸��� ���� �־��ش�.
void MakeFileName(char*& Filename, const int& Namelen, char*& name, const char* Folder, const char* extension);
/*{
	Filename = new char[Namelen + strlen(Folder) + strlen(extension)];
	Filename = strcpy(Filename, Folder);
	Filename = strcat(Filename,name);
	Filename = strcat(Filename, extension);
}*/

bool Check_Combination(int r, int g, int b);