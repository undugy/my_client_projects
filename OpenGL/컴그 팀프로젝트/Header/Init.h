#pragma once
#include "header.h"


//OBJ�� �а� ���ε����ִ� �Լ�
void InitBuffer(GLuint& vao, GLuint vbo[], GLuint& ebo, const GLuint s_program, const char* Filename, float*& vPosData, float*& vNormalData, float*& vTextureCoordinateData, int*& indexData, int& vertexCount, int& indexCount);

//�ؽ��ĸ� ���ε� ���ִ� �Լ�
void InitTexture(unsigned int& texture, int& width, int& height, int& nrChannels, const GLuint s_program, const char* Filename);
