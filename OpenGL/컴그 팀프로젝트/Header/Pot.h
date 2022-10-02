#pragma once
#include"Init.h"

#define PHEIGHT 1.3f
#define SPEED 5.0f

class Pot
{
	GLuint vao, vbo[3], ebo;

	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	int width, height, nrChannels;
	unsigned int texture;

	float SWRa = 0.0f; // �������� ����
	int delta_SWT = 1, delta_SW = 1; // ������ȭ�� ���� ����
	int PotCount = 0;
	

	//��ȯ���
	glm::mat4 SW = glm::mat4(1.0f);   //���� ��鸲 ���
	glm::mat4 SWT = glm::mat4(1.0f);  //���� ȸ������ �������� �̵����
	glm::mat4 SWT2 = glm::mat4(1.0f); //���� ȸ������ ����ġ��Ű�� �̵����
	glm::mat4 SWR = glm::mat4(1.0f);  //���� ��鸲 ȸ�� ���Rz

	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 POT = glm::mat4(1.0f); //������ �̵� ���� ȸ���� �����ϴ� ���

public:

	bool potswingTimer = false;

	int Get_potcount();

	void Init(const GLuint s_program);
	void Swing(int r, int g, int b, GLuint s_program); // ���� ��鸮�� �ִϸ��̼�
	void Draw(const unsigned int modelLocation, const unsigned int vColorLocation);
};

