#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
#include "Header/Fruit.h"
#include "Header/Camera.h"
#include "Header/Pot.h"
#include"Header/Tree1.h"

extern GLuint s_program;

extern unsigned int viewLocation;
extern Camera cm;

extern bool fruitTimer;
extern bool treeTimer;
extern bool bMakePoketmon;

extern float treeAngle;
extern int CheckCount;
extern float Red;
extern float Green;
extern float Blue;
extern float cam_dist;
extern bool RDraw;

extern bool bCheckColor;
extern bool bReset;
extern bool all_timer;
extern CType color;

extern Pot p;
extern Pokemon_Manager pm;
extern Tree1 t1;

float tempZAt=-1.0f,tempZPos=23.5f; //���Ѽ��� �Ѿ����� ������ǥ�� �־��ֱ� ���� ����
float tempXAt=0.0f, tempXPos=0.0f;
float tempYAt = 0.5f, tempYPos = 23.0f;
void Keyboard(unsigned char key, int x, int y)
{
    //������ �޼���
    cout << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamY " << cm.CamPosY << " " << "CamZ " << cm.CamPosZ << " " << endl;
    cout/* << "CamAtX" << CamAtX << " " */ << "CamATY " << cm.CamYAt << " " << "CamATZ " << cm.CamZAt << " " << endl;
    cout /*<< "CamX" << CamPosX << " " */ << "CamRotate " << cm.cam_rotate << " " << "CamRevolve " << cm.cam_revolve << " " << endl;
    cout << CheckCount << endl;
    cout << cam_dist << endl;
    cout << endl;
    switch (key)
    {
    
    case 'm':
        if (all_timer == false)
        {
     
            treeTimer = !treeTimer;
            fruitTimer = !fruitTimer;
            t1.treeAngle = 0.0f;
        }
        //treeAngle = 0.0f;
        break;
    case 'e'://��
        if (cam_dist < 34.0f)
        {
            if (cam_dist <= 33.5f)
            {
                tempYAt = cm.CamYAt; //��ǥ�� �����ֱ��� ��ǥ�� �־���´�.
                tempYPos = cm.CamPosY;
            }
            cm.CamYAt += 0.5;
            cm.CamPosY += 0.5;

        }
        if (cam_dist >= 34.f)//���� ��ǥ�� ���Ѽ���������
        {
            cm.CamYAt = tempYAt; //������ �޾Ƴ��Ҵ� ��ǥ�� �޾��ش�.
            cm.CamPosY = tempYPos;
        }
        break;
    case 'E'://�Ʒ�
        if (all_timer == false)
        {
            
            if (cam_dist < 34.0f)
            {
                if (cam_dist <= 33.5f)
                {
                    tempYAt = cm.CamYAt;
                    tempYPos = cm.CamPosY;
                }
                cm.CamYAt -= 0.5;
                cm.CamPosY -= 0.5;

            }
            if (cam_dist >= 34.f)
            {
                cm.CamYAt = tempYAt;
                cm.CamPosY = tempYPos;
            }
        }
        break;
    case 's'://��
        if (all_timer == false )
        {
            
            if (cam_dist < 34.0f)
            {
                if (cam_dist <= 33.5f)
                {
                    tempZAt = cm.CamZAt;
                    tempZPos = cm.CamPosZ;
                }
                cm.CamZAt += 0.5;
                cm.CamPosZ += 0.5;
               
            }
            if (cam_dist >=34.f)
            {
                cm.CamZAt= tempZAt;
                cm.CamPosZ= tempZPos;
            }
        }
        
        break;
    case 'w'://��
        
        if (all_timer == false)
        {
            
            if (cam_dist < 34.0f)
            {
                if (cam_dist <= 33.5f)
                {
                    tempZAt = cm.CamZAt;
                    tempZPos = cm.CamPosZ;
                }
                cm.CamZAt -= 0.5;
                cm.CamPosZ -= 0.5;

            }
            if (cam_dist >= 34.f)
            {
                cm.CamZAt = tempZAt;
                cm.CamPosZ = tempZPos;
            }
        }
   
        break;
    case'a'://��
        if (all_timer == false )
        {
            
            if (cam_dist < 34.0f)
            {
                if (cam_dist <= 33.5f)
                {
                    tempXAt = cm.CamXAt;
                    tempXPos = cm.CamPosX;
                }
                cm.CamXAt -= 0.5;
                cm.CamPosX -= 0.5;

            }
            if (cam_dist >= 34.f)
            {
                cm.CamXAt = tempXAt;
                cm.CamPosX = tempXPos;
            }
          
        }
  
        break;
    case'd'://��
        if (all_timer == false)
        {
            
            if (cam_dist < 34.0f)
            {
                if (cam_dist <= 33.5f)
                {
                    tempXAt = cm.CamXAt;
                    tempXPos = cm.CamPosX;
                }
                cm.CamXAt += 0.5;
                cm.CamPosX += 0.5;

            }
            if (cam_dist >= 34.f)
            {
                cm.CamXAt = tempXAt;
                cm.CamPosX = tempXPos;
            }

        }
        break;
    case 'y':
        if (all_timer == false && cam_dist < 35.1f)
        {
            cm.cam_rotate += 10.0;
        }
        break;
    case 'Y':
        if (all_timer == false && cam_dist < 35.1f)
        {
            cm.cam_rotate -= 10.0;
        }
        break;
    case 'r':
        if (all_timer == false && cam_dist < 35.1f)
        {
            cm.cam_revolve += 10.0;
        }
        break;
    case 'R':
        if (all_timer == false && cam_dist < 35.1f)
        {
            cm.cam_revolve -= 10.0;
        }
        break;

    case'+':
        all_timer = true;
        cm.cam_revolve = 0.0f;
        cm.cam_rotate = 0.0f;
        bMakePoketmon = true;//�� ���սý��� ����
        bReset = true;
        
        break;
    case '1'://�������� ����
        if (bMakePoketmon)
        {
            RDraw = true;
            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 1.0f;
                Green = 0.0f;
                Blue = 0.0f;
                color = CType::RED;
            }
        }
        break;
    case '2'://�ʷ� ���� ����
        if (bMakePoketmon)
        {
            RDraw = true;

            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 0.0f;
                Green = 1.0f;
                Blue = 0.0f;
                color = CType::GREEN;
            }
        }
        break;
    case'3'://�Ķ� ���� ����
        if (bMakePoketmon)
        {
            RDraw = true;
            if (CheckCount < 9)
            {

                ++CheckCount;
                Red = 0.0f;
                Green = 0.0f;
                Blue = 1.0f;
                color = CType::BLUE;
            }
        }
        break;
    case'-'://���Ż���(�ӽ�)
        
        RDraw = false;
        if (CheckCount >0)
        {   
            CheckCount--;
            
            Red = 0.0f;
            Green = 0.0f;
            Blue = 0.0f;
            color = CType::NONE;
        }
        break;

    case'o'://���� ��ġ Ȯ��Ű
        if (CheckCount >=8)
        {
           
            cm.CamPosY = 3.5f;
            cm.CamPosZ = 16.0f;
            cm.CamYAt = 3.0f;
            cm.CamZAt = 6.5f;
            bMakePoketmon = false;
            p.potswingTimer = true;
           
            bCheckColor = true;
        }
        break;

    }

    

    glutPostRedisplay();
}