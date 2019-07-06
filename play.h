#pragma once
#include <stdio.h>
#include <Windows.h>
#include <graphics.h>                   //图形库
#include <conio.h>                      //图形库
#include <easyx.h>                      //图形库

//演奏音乐 
void play() {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) 
	{
		loadimage(&bkimg, _T("图片素材\\自由弹奏.jpg"));
		k = 0;
	}
	putimage(-150, -100, &bkimg);
	settextstyle(30, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);		        // 设置文字背景为透明色
	LPCTSTR y1 = _T("Q—U键  第四八度");
	outtextxy(400, 100, y1);
	LPCTSTR y2 = _T("A—J键  第五八度");
	outtextxy(400, 150, y2);
	LPCTSTR y3 = _T("Z—M键  第六八度");
	outtextxy(400, 200, y3);

	settextstyle(25, 0, _T("微软雅黑"));
	LPCTSTR y = _T("按Esc键返回主菜单");
	outtextxy(10, 10, y);

	settextstyle(30, 0, _T("微软雅黑"));

	char voice;
	int height, dimension;
	while (1) {
		voice = getch();
		if (voice == 'q' || voice == 'w' || voice == 'e' || voice == 'r' || voice == 't' || voice == 'y' || voice == 'u')
			dimension = 4;
		else if (voice == 'a' || voice == 's' || voice == 'd' || voice == 'f' || voice == 'g' || voice == 'h' || voice == 'j')
			dimension = 5;
		else if (voice == 'z' || voice == 'x' || voice == 'c' || voice == 'v' || voice == 'b' || voice == 'n' || voice == 'm')
			dimension = 6;
		else
			dimension = -1;

		if (voice == 'q' || voice == 'a' || voice == 'z')
			voice = '1';
		else if (voice == 'w' || voice == 's' || voice == 'x')
			voice = '2';
		else if (voice == 'e' || voice == 'd' || voice == 'c')
			voice = '3';
		else if (voice == 'r' || voice == 'f' || voice == 'v')
			voice = '4';
		else if (voice == 't' || voice == 'g' || voice == 'b')
			voice = '5';
		else if (voice == 'y' || voice == 'h' || voice == 'n')
			voice = '6';
		else if (voice == 'u' || voice == 'j' || voice == 'm')
			voice = '7';
		else if (voice ==27)
			break;
		else
			voice = '-1';

		height = GET_VOICE_HEIGHT('1', voice, dimension);     //获取频率 
		Beep(height, 500);                                    //发声 
	}
}