#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include "Header/Tree1.h"
#include "Header/Tree2.h"
#include "Header/Pot.h"
#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
#include "Header/Sound.h"
#include "Header/Fruit.h"
#include "Header//background.h"
#include "Header/Camera.h"
#include "Header/Function.h"
#include "Header/CLight.h"
//opengl ���̴��� �ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);

//-------���콺�Լ�---------
void MouseInput(int button, int state, int x, int y);
void Convert_ScreenToClipSpace(int* pInX, int* pInY,
	float* pOutX, float* pOutY);
//--------------------------

//opengl �⺻����
GLuint s_program;
GLuint shaderID;
GLchar* vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;

//�����̼� ����
unsigned int flagLocation;
unsigned int vColorLocation;
unsigned int projectionLocation;
unsigned int modelLocation;
unsigned int viewLocation;
unsigned int viewposLocation;

unsigned int lightPosLocation;
unsigned int lightColorLocation;

//ī�޶� ����

//ī�޶� ��� �ֵ� ����ֵ� ������ ���� ���� 


float cam_dist;//������ ī�޶��� �Ÿ�
//Ÿ�̸� ����
bool fruitTimer = false;
bool treeTimer = false;
//bool potswingTimer = false;
bool bMakePoketmon = false;// �� ���� �ý��� üũ
bool bCheckColor = false;//�÷�üũ ������ ���߱� ���� ����
bool bReset = false;
bool all_timer = false;//��ü��� �ٱͱ� ������ �������� �ʱ� ���� üũ
void make_dist(float x, float y,float z);//�Ÿ�����Լ�

//���� ��������--------------------------------------------
void Init_fruit();// ���� ���� ��ġ����� �Լ�
GLUquadric* qobj;
float fruit_xpos[FRUIT_MAX] = { -1.5f,-1.0f, 0.5f,1.3f,1.6 };
float fruit_ypos[FRUIT_MAX] = { 0.0f, };
float fruit_zpos[FRUIT_MAX] = { -9.0f,-8.5f,-8.3f,-8.7f,-8.0f };

//----���� ����------------------
CType color; // ������ Ŭ���� �������� 0:���� ,1:���� ,2:�ʷ� , 3:�Ķ�
float Red = 0.0f;
float Green = 0.0f;
float Blue = 0.0f;
bool RDraw=false; //�������� ������ �������ִ� ����
int CheckCount = 0; //�����ϴ� �� �ε��� ī��Ʈ
int RedCount = 0;   //�÷��ǰ����� �޾��ֱ����� ����
int GreenCount = 0;	//�÷��ǰ����� �޾��ֱ����� ����
float LightCount = 0;
int BlueCount = 0;	//�÷��ǰ����� �޾��ֱ����� ����
//int PotCount = 0;
void check_color();//�÷� ī��Ʈ�� üũ���ִ� �Լ��� �迭�� �ѹ� ���Ƽ� ��� �÷��� ������ üũ
void reset();//�丮����� �ʱ�ȭ�ϱ� �����Լ�
//------------------------------


//��� ����

glm::mat4 projection = glm::mat4(1.0f);



//��ü ����
Bottom b;
Tree1 t1;
Tree2 t2;
Pot p;
Fruit SysFruit[SYSTEM_FRUIT_MAX]; //���տ� ���� ��ü
CLight light;
Pokemon_Manager pm;
Sound sound;
Background bg;
Camera cm;

void main(int argc, char** argv)
{
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("PokeMonSimulator");

	glewExperimental = GL_TRUE;
	glewInit();

	glUseProgram(s_program);

	InitShader();

	//Ŭ���� �ʱ�ȭ------------------
	b.Init(s_program);
	t1.Init(s_program);
	t2.Init(s_program);
	p.Init(s_program);

	//����
	sound.Init_Sound();
	//���
	bg.Init(s_program);
	cm.Init();
	
	//-------------------
	qobj = gluNewQuadric();
	//-----����� �Լ�--------
	Init_fruit();
	
	//--------------------

	//�����̼� ����
	flagLocation = glGetUniformLocation(s_program, "flag");
	vColorLocation = glGetUniformLocation(s_program, "in_Color");
	projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
	modelLocation = glGetUniformLocation(s_program, "modelTransform");
	viewLocation = glGetUniformLocation(s_program, "viewTransform");
	viewposLocation = glGetUniformLocation(s_program, "viewPos");
	lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	
	//��������
	FMOD_System_PlaySound(sound.soundSystem, sound.bgmSound[0], NULL, 0, &sound.Channel[0]);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseInput);
	glutTimerFunc(10, Timerfunction, 1);

	glutMainLoop();

}

//�ݹ��Լ�

GLvoid drawScene()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glm::mat4 T = glm::mat4(1.0f);
	
	cm.Update(viewLocation);
	light.Update(lightPosLocation, lightColorLocation);
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	glUseProgram(s_program);
	glEnable(GL_DEPTH_TEST);
	glUniform1i(flagLocation, 0);

	// ���׷���

	bg.Draw(modelLocation);

	//--------------------�ٴ�
	b.Draw(modelLocation);
	//----------------------

	//---------------------�ڿ� ������
	for (int i = 2; i < 12; ++i)
	{
	
		t1.DrawBackTree(modelLocation,i);
		t1.DrawBackTree(modelLocation, -i);
		
	}
	//----------------------------------------


	//-------------------���� ū����
	
	t1.DrawBigTree(modelLocation);
	
	//------------����
	glUniform1i(flagLocation, 1);
	for (int i = 0; i < FRUIT_MAX; ++i)
	{
		

		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)fruit_xpos[i], fruit_ypos[i], (float)fruit_zpos[i]));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
		if(i==1)
		glUniform3f(vColorLocation,1.0f, 0.0f, 0.0f);
		if(i>1&&i<=3)
			glUniform3f(vColorLocation, 0.0f, 1.0f, 0.0f);
		if(i>3)
			glUniform3f(vColorLocation, 0.0f, 0.0f, 1.0f);
		gluSphere(qobj, 0.2, 20, 20);
	}
	
	glUniform1i(flagLocation, 0);
	//-------------------------------���� ������

	for (int i = 1; i < 23; ++i)
	{
		float chp;
		if (i % 2 == 0)
			chp = -0.7;
		else
			chp = 0.7;
		
		if (i % 2 == 0)
		{
			t1.DrawSideTree(modelLocation, chp, i, -11.0);
			t1.DrawSideTree(modelLocation, -chp, i, 11.0);
		}
		else
		{
			t2.DrawSideTree(modelLocation,chp,i,-11.0);
			t2.DrawSideTree(modelLocation, -chp, i, 11.0);
		}
	}

	//--------------------------------------------------
	pm.Draw(modelLocation);

	//------------------------------------------------��
	glUniform1i(flagLocation, 0);
	p.Draw(modelLocation,vColorLocation);
	//--------------------���� ����

	if (bMakePoketmon)
	{
		if (RDraw)
		{
			//Ű���� �������� �޾ƿ� ���� �־���
			SysFruit[CheckCount-1].Create(RDraw,Red,Green, Blue, color);
		}
		else
		{
			//������ RDraw�� false�� ����� rkqtdmf sjgdjwna
			SysFruit[CheckCount].Remove(false);
		}
		for (int i = 0; i < 9; ++i)
		{
			glUniform1i(flagLocation, 1);
			SysFruit[i].Draw(modelLocation,vColorLocation);
		}
		
	}
	
	glutSwapBuffers();
}



void Timerfunction(int value)
{
	make_dist(cm.CamPosX, cm.CamPosY, cm.CamPosZ);
	LightCount += 0.05;
	light.movelight(LightCount);
	if (treeTimer)
		t1.Swing();
	if (fruitTimer)
	{
		
		for (int i = 0; i < FRUIT_MAX; ++i)
		{
			fruit_ypos[i] -= (rand() % 10 + 1) * 0.01;
			if (fruit_ypos[i] <= 1.5f)
			{
				fruit_ypos[i] = 1.5f;
			}
		}
	}
	if (all_timer)
	{
		if (bMakePoketmon)
		{
			if (bReset)
			{
				reset();
				bReset = false;
			}
			cm.make_pot_cam();
		}
		else
		{
			if (bCheckColor)
			{
				check_color();
				bCheckColor = false;
				CheckCount = 0;
			}
			else
				p.Swing(RedCount, GreenCount, BlueCount, s_program);


		}

		pm.Act();

		if (pm.Position_timer) pm.Position_Count += 1;

		if (pm.Position_Count >= 100)
		{
			pm.Position();
			pm.Position_Count = 0;
			pm.Position_timer = false;
			cm.make_Overview();
			all_timer = false;
		}
	}
	else
	pm.Act();
	glutTimerFunc(10, Timerfunction, 1);
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Init_fruit()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < FRUIT_MAX; ++i)
	{
		float fch = (rand() % 10 + 1) / 100+1;//��ġ ����ȭ ����(�յ� �翷)
		if (i % 2 == 0)
		{
			fch *= -1;
		}
		//fruit_zpos[i] = -10.0 + fch;
		//fruit_xpos[i] =fch+i/10;
		fruit_ypos[i] = 9.0f;
	}
	
	for (int i = 0; i < 3; ++i)
	{
		SysFruit[i].x = -0.65f + (i * 0.65);
		SysFruit[i].y = 3.4f;
		SysFruit[i].z = 1.3f;

		SysFruit[i+3].x = -0.65f + (i * 0.65);
		SysFruit[i+3].y = 3.4f;
		SysFruit[i+3].z = 1.95f ;

		SysFruit[i + 6].x = -0.65f + (i * 0.65);
		SysFruit[i + 6].y = 3.4f;
		SysFruit[i + 6].z =  2.6;
	}

	
}

// ���� �������� ���� �� ���� �ݱ�
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	
		float fOutX;
		float fOutY;
		Convert_ScreenToClipSpace(&x, &y, &fOutX, &fOutY);
		cout << fOutX << "|" << fOutY << endl;
		
			for (int i = 0; i < FRUIT_MAX; ++i)
			{
				fruit_ypos[i] = 9.0f;

			}
		//������ �ö󰡰Ը���
		//��ǥ �浹�� ������ �����Ƿ� Ű����� ��ȯ�ϰų� ���д�.
	}
}



//ī�޶� ��� �ֵ� ����ֵ� ������ ���� ���� 


void check_color()
{
	//��ü�� ������ �ִ� �������� ���� ī��Ʈ�� ���ش�.
	for (int i = 0; i < SYSTEM_FRUIT_MAX; ++i)
	{
		if (SysFruit[i].color == CType::RED)
			++RedCount;
		else if (SysFruit[i].color == CType::GREEN)
			++GreenCount;
		else if (SysFruit[i].color == CType::BLUE)
			++BlueCount;
	}
	cout << RedCount<<"|" << GreenCount<<"|" << BlueCount << endl; //üũ��
	
}

void reset()
{
	for (int i = 0; i < 9; ++i)
	{
		bool r = false;
		SysFruit[i].Remove(r);
	}
	RedCount = 0;
	GreenCount = 0;
	BlueCount = 0;
	CheckCount = 0;
	color = CType::NONE;
	Red = 0.0f;
	Green = 0.0f;
	Blue = 0.0f;
	
}

void make_dist(float x, float y, float z)
{
	cam_dist = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}