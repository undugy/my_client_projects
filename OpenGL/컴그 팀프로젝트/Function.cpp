#include "Header/Function.h"



float NCV(float value)
{
	return value / 255.0f;
}


void MakeFileName(char*& Filename, const int& Namelen,char*& name, const char* Folder, const char* extension)
{
	Filename = new char[Namelen + strlen(Folder) + strlen(extension)];
	strcpy(Filename, Folder);
	strcat(Filename, name);
	strcat(Filename, extension);
}

void Convert_ScreenToClipSpace(int* pInX, int* pInY, //��ũ����ǥ->�������� ��ǥ
	float* pOutX, float* pOutY)//��ũ�� ���� ���콺 ��ǥ�� �������� ��ǥ��� �ٲ��ִ� �Լ�
{
	*pOutX = (*pInX - WIDTH / 2) * 2.f / WIDTH;
	*pOutY = (HEIGHT / 2 - *pInY) * 2.f / HEIGHT;
}

bool Check_Combination(int r, int g, int b)
{
	if (b == 9)
	{
		return 1;
	}
	else if (r == 6 && g == 3)
	{
		return 1;
	}
	else if (g == 9)
	{
		return 1;
	}
	else if (r == 7 && g == 1 && b == 1)
	{
		return 1;
	}
	else if (r == 3 && g == 3 && b == 3)
	{
		return 1;
	}
	else  return 0;
}