#pragma once
#include "Init.h"

class Bottom {

	GLuint vao, vbo[3],ebo;

	//���� ����
	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	//�ؽ�ó ����
	int width, height, nrChannels;
	unsigned int texture;

	//��ȯ ���
	glm::mat4 S = glm::mat4(1.0f); 
	glm::mat4 BOT = glm::mat4(1.0f); // �ٴ��� ���� �̵� ȸ���� �����ϴ� ���
public:

	void Init(const GLuint s_program);
	void Draw(const unsigned int modelLocation);
};
