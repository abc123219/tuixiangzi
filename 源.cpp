
#include <iostream>
#include <stdlib.h>
#include <string>
#include <graphics.h>
#include <conio.h>//获取热键的头文件

using namespace std;

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

/*******************************************************
*改变游戏地图视图中一格对应道具并重新显示
*输入:
*		line    道具的行下标
*		column  道具的列下标
*		prop	道具的类型
********************************************************/
void changeMap(int line, int column, enum _PROPS prop)
{
	map[line][column] = prop;//把道具保存
	//显示出来
	putimage(column * RATIO + START_X, line * RATIO + START_Y, &images[prop]);
}


/********************************************************
*实现游戏四个方向的控制
*输入:
*	direct   人前进的方向
*
*********************************************************/
void gameControl(enum _DIRECTION direct)
{

	//定义人物下一个道具的坐标变量
	struct _Pos next_pos = coor_xy;


	//根据方向获取下一个坐标位置
	switch (direct) {
		case UP:
			next_pos.x--;
			break;
		case DOWN:
			next_pos.x++;
			break;
		case LEFT:
			next_pos.y--;
			break;
		case RIGHT:
			next_pos.y++;
			break;
	}

	//ISVALID(next_pos)范围 
	if (ISVALID(next_pos) && map[next_pos.x][next_pos.y] == FLOOR)
	{
		//人物位置和移动方向的下一个位置互换
		changeMap(next_pos.x, next_pos.y, MAN);
		changeMap(coor_xy.x, coor_xy.y, FLOOR);

		//人物位置变成移动方向的下一个位置
		coor_xy = next_pos;
	}
	if (map[next_pos.x][next_pos.y] == BOX)
	{
		if (direct == UP)
		{
			if (map[next_pos.x][next_pos.y] == FLOOR)
			{
				changeMap(next_pos.x - 1, next_pos.y, BOX);
				changeMap(next_pos.x, next_pos.y, MAN);
				changeMap(coor_xy.x, coor_xy.y, FLOOR);

				coor_xy = next_pos;
			}

		}
		
	}



	/*普通版
	if (direct == UP)
	{
		//检测人物范围		和人物移动方向前的物体是什么
		if ((x - 1) >= 0 && map[x - 1][y] == FLOOR)
		{
			//地板和人物互换
			changeMap(x - 1, y, MAN);//设为人物
			changeMap(x, y, FLOOR);//设为地板

			coor_xy.x = x - 1;//修改人物坐标
		}
	}
	else if (direct == DOWN)
	{
		//检测人物范围		和人物移动方向前的物体是什么
		if ((x + 1) < LINE && map[x + 1][y] == FLOOR)
		{
			//人物和道具互换
			changeMap(x + 1, y, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.x = x + 1;//修改人物坐标
		}
	}
	else if (direct == LEFT)
	{
		//检测人物范围		和人物移动方向前的物体是什么
		if ((y - 1) >= 0 && map[x][y - 1] == FLOOR)
		{
			//人物和道具互换
			changeMap(x, y - 1, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.y = y - 1;//修改人物坐标
		}
	}
	else if (direct == RIGHT)
	{
		//检测人物范围		和人物移动方向前的物体是什么
		if ((y + 1) < COLUMN&&map[x][y + 1] == FLOOR)
		{
			//人物和道具互换
			changeMap(x, y + 1, MAN);
			changeMap(x, y, FLOOR);

			coor_xy.y = y + 1;//修改人物坐标
		}
	}
	*/
}





int main32(void)
{
	IMAGE bg_img;

	initgraph(SCREEN_WLDTH, SCREEN_HEIGHT);//设置窗口大小
	//加载   背景图片								图片大小				是否图片延申
	loadimage(&bg_img, _T("blackground.bmp"), 
		SCREEN_WLDTH, SCREEN_HEIGHT, true);

	putimage(0, 0, &bg_img);//打印图片  在那个坐标开始打印

	//获取图片          加载道具
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
			//获取角色的坐标位置
			if (map[i][j] == MAN)
			{
				coor_xy.x = i;
				coor_xy.y = j;
			}

			putimage(j * RATIO + START_X, i * RATIO + START_Y, &images[map[i][j]]);
		}
	}

	//游戏环节
	bool quit = false;//退出

	/*
	#define KEY_UP		'w'
	#define KEY_LEFT	'a'
	#define KEY_RIGHT	'd'
	#define KEY_DOWN	's'
	#define KEY_QUIT	'q'
	*/
	do
	{
		if (_kbhit())//玩家有按键
		{
			char ch = _getch();

			//判断控制
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
		}
		Sleep(100);//休眠0.1秒
	} while (quit == false);//或者!quit


	system("pause");
	return 0;
}