#pragma once

#include <graphics.h>


#define ISVALID(pos)  pos.x >=0 && pos.x<LINE && pos.y >=0 && pos.y < COLUMN

#define RATIO 61		//道具大小

//终端窗口大小
#define SCREEN_WLDTH 960
#define SCREEN_HEIGHT 768

//地图排列
#define LINE 9			//行
#define COLUMN 12		//列

//道具坐标的偏移度
#define START_X 100		//X轴
#define START_Y 150		//Y轴

//热键控制
#define KEY_UP		'w'
#define KEY_LEFT	'a'
#define KEY_RIGHT	'd'
#define KEY_DOWN	's'
#define KEY_QUIT	'q'

//枚举类型		道具
enum _PROPS
{
	WALL,			//墙
	FLOOR,			//地板
	BOX_DES,		//箱子目的地
	MAN,			//人
	BOX,			//箱子
	HIT,			//箱子命中目标
	ALL
};

//游戏方向控制
enum _DIRECTION
{
	UP,			//上
	DOWN,		//下
	LEFT,		//左
	RIGHT		//右
};


struct _Pos
{
	int x;
	int y;
};

//图片数组
IMAGE images[ALL];
IMAGE bg_img;

//人的坐标
struct _Pos coor_xy;

//地图
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

//声明函数		地图
void img();

/*******************************************************
*改变游戏地图视图中一格对应道具并重新显示
*输入:
*		line    道具的行下标
*		column  道具的列下标
*		prop	道具的类型
********************************************************/
void changeMap(struct _Pos *pos, enum _PROPS prop);

/********************************************************
*实现游戏四个方向的控制
*输入:
*	direct   人前进的方向
*
*********************************************************/
void gameControl(enum _DIRECTION direct);

void control();//按键控制

/* 判断游戏是否达到结束条件 LINE][COLUMN] */
bool complete();

/* 游戏结束后,切换背景 */
void victory(IMAGE *bg_img);