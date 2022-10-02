#pragma once
#include "header.h"


class Pokemon {

	GLuint vao, vbo[3], ebo;

	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	int width, height, nrChannels;
	unsigned int texture;

	
	char* Filename, *Texturename; //�����̸�, �ؽ�ó�����̸�
	char* name; //���ϸ� �̸�
	int nsize; //���ϸ� �̸� ����
	float p_height; //���ϸ� Ű
	int Act_Type; //���Ƿ� �ൿ�� �ο��ϱ����� ����
	glm::vec3 pos; //���ϸ� ���� ��ġ

	//�� ��ȯ���
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 PKM = glm::mat4(1.0f); //���ϸ� �ʱ⼼�� ���

	glm::mat4 PT = glm::mat4(1.0f);

	//�� �ִϸ��̼�
	glm::mat4 JMP = glm::mat4(1.0f); //���� ���
	float jmpy = 0.0f;  //���� �̵���
	int delta_jy = 1;  //���� ��ȭ��
	int jumptimer = 0; //�� �������ð�

	glm::mat4 SW = glm::mat4(1.0f);  //���� ���
	glm::mat4 SWR = glm::mat4(1.0f); //���� ȸ��
	glm::mat4 SWT = glm::mat4(1.0f);  //���� ���̵�
	glm::mat4 SWT2 = glm::mat4(1.0f); //���� ���̵� ����ġ
	float SWRa = 0.0f; // �������� ����
	float sw_speed = 1.0f; // ���� �ӵ�
	int delta_SWT = 1, delta_SW = 1; // ������ȭ�� ���� ����

	glm::mat4 ROT = glm::mat4(1.0f); // ȸ��(��۹��) ���

	glm::mat4 FLO = glm::mat4(1.0f); // �յ� ���ٴϴ� ���
	int delta_fy = 1; // �յ� ��ȭ��
	float floy = 0.0f; // �յ� �̵���

public:

	// ������ ���ϸ� ������ �̸��� �����ּ���
	Pokemon(const char* n); 
	//�Ҹ���
	~Pokemon();

	int Get_Act_Type();
	int Get_PosX();
	int Get_PosZ();
	float Get_p_height();
	

	void Set_Pos(float x, float y, float z);

	void Init(const GLuint s_program);

	//���ϸ� �̸������� ������ �ʱ�ȭ ���ִ� �Լ�
	void Has_Pokemon();

	//���ϸ� ��ġ ������
	void Position();

	void Draw(const unsigned int modelLocation);

	void Update_Pos();

	//���ϸ� �ִϸ��̼�

	//����1
	void Jump();
	// ����2 
	void Jump2();
	//���� 
	void Swing();
	//���ۺ��� 
	void Rotate();
	//�յ� 
	void Float(float _h);
	//����̵�
	void Tornado();

};

