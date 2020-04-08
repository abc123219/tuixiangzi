#pragma once

#include <graphics.h>


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