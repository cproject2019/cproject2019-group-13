#pragma once
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define random() (rand())
#pragma comment(lib,"Winmm.lib")


int score = 0;         //总得分
int comboscore = 0;    //当前combo
int maxcomboscore = 0; //最大连击
int good_flag = 0;     //是否显示 GOOD 图片
int restart = 0;       //是否重新开始游戏


//输出图片
void myoutimg(my_img* my, IMAGE *yanma)
{
	if (yanma == NULL)
	{
		// 恢复区域
		putimage(my->x, my->y, &my->before);
	}
	else
	{
		int w = my->img.getwidth();  	// 获取图片占用的宽度
		int h = my->img.getheight();	// 获取图片占用的高度
		getimage(&my->before, my->x, my->y, w, h);		  // 保存区域
		// 图片输出
		putimage(my->x, my->y, yanma, SRCAND);
		putimage(my->x, my->y, &my->img, SRCPAINT);
	}
}

//初始化游戏背景
void static_game() {
	//图片输出
	static IMAGE bkimg;         //背景图
	static my_img combo;        //combo背景图
	static my_img maxcombo;     //maxcombo背景图
	static IMAGE combo_mask;    //combo掩码图

	static char UseForInitialOnlyOnce = 1;  //只初始化一次
	if (UseForInitialOnlyOnce == 1) {
		UseForInitialOnlyOnce = 0;
		loadimage(&bkimg, _T("图片素材\\弹奏评分.jpg"));
		loadimage(&combo.img, _T("图片素材\\combo.jpg"));
		loadimage(&maxcombo.img, _T("图片素材\\combo.jpg"));
		combo.y = 370;   combo.x = 80 + 13;         //combo背景图坐标
		maxcombo.y = 370;   maxcombo.x = 420 + 13;  //maxcombo背景图坐标
	}
	putimage(0, 0, &bkimg);

	myoutimg(&combo, &combo_mask);                //不破坏背景地输出图片
	myoutimg(&maxcombo, &combo_mask);

	setcolor(WHITE);
	setbkmode(TRANSPARENT);		        // 设置文字背景为透明色
	settextstyle(22, 0, _T("微软雅黑"));
	outtextxy(195 + 16, 0, _T("左轨道按D键      右轨道按J键"));
	settextstyle(25, 0, _T("微软雅黑"));
	outtextxy(10, 10, _T("退出按ESC键"));
}

//更新游戏内的动态信息
void Update() {
	//图片输出:
	static my_img gd;        //good图片结构
	static IMAGE gd1;        //good掩码图
	static char UseForInitialOnlyOnce = 1;  //只初始化一次
	if (UseForInitialOnlyOnce == 1) {
		loadimage(&gd.img, _T("图片素材\\good.jpg"));
		loadimage(&gd1, _T("图片素材\\good掩码图.jpg"));
		UseForInitialOnlyOnce = 0;
		gd.x = 89; gd.y = 300;
	}
	if (good_flag) {
		myoutimg(&gd, &gd1);
		good_flag--;
	}


	//文字输出:

	//得分输出
	settextstyle(23, 0, _T("微软雅黑"));     //设置字体
	settextcolor(YELLOW);					 // 设置文字颜色为黄色
	setbkmode(TRANSPARENT);					 // 设置文字背景为透明色	
	outtextxy(500, 100, _T("Score:"));
	TCHAR s[5];								 //声明数组，用来存放字符串
	_stprintf(s, _T("%d"), score);			 //将整形score转换成字符串
	outtextxy(560, 100, s);	                 //将字符串输出到界面上

											 //当前combo输出
	settextstyle(21, 0, _T("微软雅黑"));     //设置字体
	settextcolor(RED);						 // 设置文字颜色为红色
	setbkmode(TRANSPARENT);					 // 设置文字背景为透明色
	outtextxy(115 + 4, 395, _T("Combo"));
	TCHAR s1[5];							 //声明数组，用来存放字符串
	_stprintf(s1, _T("%d"), comboscore);     //将整形comboscore转换成字符串
	outtextxy(130 + 10, 420, s1);            //将字符串输出到界面上

											 //最大连击输出										 
	settextcolor(RED);						 // 设置文字颜色为红色
	setbkmode(TRANSPARENT);					 // 设置文字背景为透明色
	outtextxy(438, 395, _T("MAX combo"));
	TCHAR s2[5];							 //声明数组，用来存放字符串
	_stprintf(s2, _T("%d"), maxcomboscore);  //将整形maxcomboscore转换成字符串
	outtextxy(130 + 340 + 15, 420, s2);        //将字符串输出到界面上
}

//双轨道
void track(int isR, int isL) {
	static my_img diamond_left[5];  //定义左轨道水晶条变量数组
	static my_img diamond_right[5]; //定义右轨道水晶条变量数组
	static IMAGE diamond_mask;      //水晶条掩码图
	//初始化								
	static char UseForInitialOnlyOnce = 1; //只初始化一次
	if (UseForInitialOnlyOnce == 1)
		for (int i = 0; i < 5; i++) {
			loadimage(&diamond_left[i].img, _T("图片素材\\水晶条.jpg"));  //70 x 18
			diamond_left[i].flag = 0;
			diamond_left[i].x = 184 + 19 + 14;
			diamond_left[i].isgetd = 0;
			loadimage(&diamond_right[i].img, _T("图片素材\\水晶条.jpg"));  //70 x 18
			diamond_right[i].flag = 0;
			diamond_right[i].x = 184 + 145 + 14;
			diamond_right[i].isgetd = 0;
			loadimage(&diamond_mask, _T("图片素材\\水晶条掩码图.jpg"));  //70 x 18
			UseForInitialOnlyOnce = 0;
		}
	static int p = 0;  //p控制随机生成的速度


	if (isL == 1) {
		for (int i = 0; i < 5; i++) {
			if (diamond_left[i].flag == 0) {
				diamond_left[i].flag = 1;                            //可以显示
				diamond_left[i].y = 76;								 //下落纵坐标初始化
				break;												 //只生成一个
			}

		}
	}
	if (isR == 1) {
		for (int i = 0; i < 5; i++) {
			if (diamond_right[i].flag == 0) {
				p = 0;
				diamond_right[i].flag = 1;							 //可以显示
				diamond_right[i].y = 76; 							 //下落纵坐标初始化
				break;												 //只生成一个
			}
		}
	}

	//水晶条下落，分别处理左右轨道，完全类似，此为左轨道
	for (int i = 0; i < 5; i++) {
		if (diamond_left[i].flag == 1) {            //该显示的才下落
													//得分条件
			if (diamond_left[i].isgetd == 0 && diamond_left[i].y >= 420 & diamond_left[i].y < 427) {
				if (GetAsyncKeyState(0x44) & 0x8000) {       //按 d 键
					score += 10;                               //加分
					comboscore++;                            //当前combo+1
					diamond_left[i].isgetd = 1;              //得分后该条水晶条不能再被得分
					good_flag = 30;							 //可以显示 GOOD
				}
			}
			//未到底，输出水晶条
			if (diamond_left[i].y < 427) {
				myoutimg(&diamond_left[i], &diamond_mask);
			}
			//到底，处理信息
			else {
				if (diamond_left[i].isgetd == 0) {
					comboscore = 0;            //该条水晶条未被得分，当前combo重置
				}
				diamond_left[i].flag = 0;      //不可显示
				diamond_left[i].isgetd = 0;    //被得分重置
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (diamond_right[i].flag == 1) {            //该显示的才下落
													 //得分条件
			if (diamond_right[i].isgetd == 0 && diamond_right[i].y >= 420 & diamond_right[i].y < 427) {
				if (GetAsyncKeyState(0x4A) & 0x8000) {       //按 j 键
					score += 10;                       //加分
					comboscore++;
					diamond_right[i].isgetd = 1;        //得分后该条水晶条不能再被得分
					good_flag = 30;
				}
			}
			//未到底，输出水晶条
			if (diamond_right[i].y < 427) {
				myoutimg(&diamond_right[i], &diamond_mask);
			}
			else {
				if (diamond_right[i].isgetd == 0) {
					comboscore = 0;
				}
				diamond_right[i].flag = 0;
				diamond_right[i].isgetd = 0;
			}
		}
	} //处理右轨道，完全类似

	if (comboscore > maxcomboscore) {
		maxcomboscore = comboscore;    //处理最大连击
	}

	//延时
	Sleep(10);
	FlushBatchDraw();                  //批量绘图

									   //恢复原状并让水晶条下落，分别处理左右轨道，完全类似
	for (int i = 0; i < 5; i++) {
		if (diamond_left[i].flag == 1) {
			if (diamond_left[i].y < 427) {
				myoutimg(&diamond_left[i], NULL);  //恢复原状
				diamond_left[i].y += 4;               //水晶条下落
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (diamond_right[i].flag == 1) {
			if (diamond_right[i].y < 427) {
				myoutimg(&diamond_right[i], NULL);
				diamond_right[i].y += 4;
			}
		}
	}
}

//其他功能的实现
int UpdateWithInput(void) {
	int flag = -1;
	if (_kbhit()) {
		char c = _getch();
		if (c == 27) {                             //27->ESC键
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);//关闭音乐
			return 1;
		}
	}
	return flag;
}