#include <iostream>
#include <stdlib.h>
#include <string>
#include <graphics.h>
#include <conio.h>//��ȡ�ȼ���ͷ�ļ�

using namespace std;

#define ISVALID(pos)  pos.x >=0 && pos.x<LINE && pos.y >=0 && pos.y < COLUMN

#define RATIO 61		//���ߴ�С

//�ն˴��ڴ�С
#define SCREEN_WLDTH 960
#define SCREEN_HEIGHT 768

//��ͼ����
#define LINE 9			//��
#define COLUMN 12		//��

//���������ƫ�ƶ�
#define START_X 100		//X��
#define START_Y 150		//Y��

//�ȼ�����
#define KEY_UP		'w'
#define KEY_LEFT	'a'
#define KEY_RIGHT	'd'
#define KEY_DOWN	's'
#define KEY_QUIT	'q'

//ö������		����
enum _PROPS
{
	WALL,			//ǽ
	FLOOR,			//�ذ�
	BOX_DES,		//����Ŀ�ĵ�
	MAN,			//��
	BOX,			//����
	HIT,			//��������Ŀ��
	ALL
};

//��Ϸ�������
enum _DIRECTION
{
	UP,			//��
	DOWN,		//��
	LEFT,		//��
	RIGHT		//��
};


struct _Pos
{
	int x;
	int y;
};

//ͼƬ����
IMAGE images[ALL];
IMAGE bg_img;

//�˵�����
struct _Pos coor_xy;

//��ͼ
int map[LINE][COLUMN] = {
{0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,1,1,1,1,1,1,1,0,0},
{0,1,4,1,0,2,1,0,2,1,0,0},
{0,1,0,1,0,1,0,0,1,1,1,0},
{0,1,0,2,0,1,1,4,1,1,1,0},
{0,1,1,1,0,3,1,1,1,4,1,0},
{0,1,2,1,1,4,1,1,1,1,1,0},
{0,1,0,0,1,0,1,1,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0}
};

//��������		��ͼ
void img();

/*******************************************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*����:
*		line    ���ߵ����±�
*		column  ���ߵ����±�
*		prop	���ߵ�����
********************************************************/
void changeMap(struct _Pos *pos, enum _PROPS prop);

/********************************************************
*ʵ����Ϸ�ĸ�����Ŀ���
*����:
*	direct   ��ǰ���ķ���
*
*********************************************************/
void gameControl(enum _DIRECTION direct);

void control();//��������

/* �ж���Ϸ�Ƿ�ﵽ�������� LINE][COLUMN] */
bool complete();

/* ��Ϸ������,�л����� */
void victory(IMAGE *bg_img);





int main(void)
{
	
	img();//��ͼ

	control();//����

	system("pause");

	closegraph();//�ͷ���Դ
	return 0;
}





//��ͼ����
void img()
{

	initgraph(SCREEN_WLDTH, SCREEN_HEIGHT);//���ô��ڴ�С
	//����   ����ͼƬ								ͼƬ��С				�Ƿ�ͼƬ����
	loadimage(&bg_img, _T("blackground.bmp"),
		SCREEN_WLDTH, SCREEN_HEIGHT, true);

	putimage(0, 0, &bg_img);//��ӡͼƬ  ���Ǹ����꿪ʼ��ӡ

	//��ȡͼƬ          ���ص���
	loadimage(&images[WALL], _T("wall_right.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);

	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			//��ȡ��ɫ������λ��
			if (map[i][j] == MAN)
			{
				coor_xy.x = i;
				coor_xy.y = j;
			}

			putimage(j * RATIO + START_X, i * RATIO + START_Y, &images[map[i][j]]);
		}
	}
}

/*******************************************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*����:
*		line    ���ߵ����±�
*		column  ���ߵ����±�
*		prop	���ߵ�����
********************************************************/
void changeMap(struct _Pos *pos, enum _PROPS prop)
{
	map[pos->x][pos->y] = prop;//�ѵ��߱���
	//��ʾ����
	putimage(pos->y * RATIO + START_X, pos->x * RATIO + START_Y, &images[prop]);
}

/********************************************************
*ʵ����Ϸ�ĸ�����Ŀ���
*����:
*	direct   ��ǰ���ķ���
*
*********************************************************/
void gameControl(enum _DIRECTION direct)
{

	//����������һ�����ߵ��������
	struct _Pos next_pos = coor_xy;			//�����ƶ������ǰһ��λ��
	struct _Pos next_next_pos = coor_xy;	//�����ƶ������ǰһ��λ��


	//���ݷ����ȡ��һ������λ��
	switch (direct) {
	case UP:
		next_pos.x--;
		next_next_pos.x -= 2;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x += 2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y -= 2;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y += 2;
		break;
	}

	//ISVALID(next_pos)��Χ 
	if (ISVALID(next_pos) && map[next_pos.x][next_pos.y] == FLOOR)//�˵�ǰ���ǵذ�
	{
		//����λ�ú��ƶ��������һ��λ�û���
		changeMap(&next_pos, MAN);
		changeMap(&coor_xy, FLOOR);

		//����λ�ñ���ƶ��������һ��λ��
		coor_xy = next_pos;
	}
	else if (ISVALID(next_next_pos) && map[next_pos.x][next_pos.y] == BOX)//�˵�ǰ��������
	{
		//�������,ǰ�������ӻ�������Ŀ�ĵ�
		//��һ��
		if (map[next_next_pos.x][next_next_pos.y] == FLOOR)
		{
			changeMap(&next_next_pos, BOX);//�������
			changeMap(&next_pos, MAN);		//�����
			changeMap(&coor_xy, FLOOR);		//��ɵذ�
			coor_xy = next_pos;

		}
		//�ڶ���
		else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES)
		{
			changeMap(&next_next_pos, HIT);//�������Ŀ�ĵ�
			changeMap(&next_pos, MAN);		//�����
			changeMap(&coor_xy, FLOOR);		//��ɵذ�
			coor_xy = next_pos;
		}
	}



	/*��ͨ��
	if (direct == UP)
	{
		//������ﷶΧ		�������ƶ�����ǰ��������ʲô
		if ((x - 1) >= 0 && map[x - 1][y] == FLOOR)
		{
			//�ذ�����ﻥ��
			changeMap(x - 1, y, MAN);//��Ϊ����
			changeMap(x, y, FLOOR);//��Ϊ�ذ�

			coor_xy.x = x - 1;//�޸���������
		}
	}
	else if (direct == DOWN)
	{
		//������ﷶΧ		�������ƶ�����ǰ��������ʲô
		if ((x + 1) < LINE && map[x + 1][y] == FLOOR)
		{
			//����͵��߻���
			changeMap(x + 1, y, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.x = x + 1;//�޸���������
		}
	}
	else if (direct == LEFT)
	{
		//������ﷶΧ		�������ƶ�����ǰ��������ʲô
		if ((y - 1) >= 0 && map[x][y - 1] == FLOOR)
		{
			//����͵��߻���
			changeMap(x, y - 1, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.y = y - 1;//�޸���������
		}
	}
	else if (direct == RIGHT)
	{
		//������ﷶΧ		�������ƶ�����ǰ��������ʲô
		if ((y + 1) < COLUMN&&map[x][y + 1] == FLOOR)
		{
			//����͵��߻���
			changeMap(x, y + 1, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.y = y + 1;//�޸���������
		}
	}
	*/
}

void control()
{
	//��Ϸ����
	bool quit = false;//�˳�

	/*
	#define KEY_UP		'w'
	#define KEY_LEFT	'a'
	#define KEY_RIGHT	'd'
	#define KEY_DOWN	's'
	#define KEY_QUIT	'q'
	*/
	do
	{
		if (_kbhit())//��������û�а��°���		�з��ط�0(��)	û�з���0(��)
		{
			char ch = _getch();//�����뻺������ȡһ���ַ�

			//�жϿ���
			if (ch == KEY_UP) {
				gameControl(UP);
			}
			else if (ch == KEY_LEFT) {
				gameControl(LEFT);
			}
			else if (ch == KEY_DOWN) {
				gameControl(DOWN);
			}
			else if (ch == KEY_RIGHT) {
				gameControl(RIGHT);
			}
			else if (ch == KEY_QUIT) {
				quit = true;
			}

			//�ж���Ϸ�Ƿ�ﵽ��������
			if (complete())
			{
				victory(&bg_img);

				quit = true;
			}
		}
		Sleep(100);//����0.1��
	} while (quit == false);//����!quit
}

/* �ж���Ϸ�Ƿ�ﵽ�������� */
bool complete()
{
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (map[i][j] == BOX_DES)return false;
		}
	}
	return true;
}

/* ��Ϸ������,�л����� */
void victory(IMAGE *bg_img)
{
	putimage(0, 0, bg_img);//��ӡ����

	settextcolor(WHITE);//��ɫ
	RECT rec = { 0,0,SCREEN_WLDTH,SCREEN_HEIGHT };
	settextstyle(20, 0,_T( "����"));

	drawtext(_T("��ϲ��,��Ϊ��������˾��."), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}